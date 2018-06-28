<xsl:transform
	xmlns:w131='http://www.witsml.org/schemas/131'
	xmlns:w140='http://www.witsml.org/schemas/1series'
	xmlns:xsl='http://www.w3.org/1999/XSL/Transform'
	xmlns:diff="http://www.posc.org/schemas/schemaDiff" 
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	version='1.1'>

  <xsl:output 
	method     = "xml" 
	media-type = "text/xml"
	encoding   = "utf-8" />

<!-- ==================================================================== -->
<!--   Transform between different two versions of WITSML XML files.      -->
<!--   The currently supported versions are (automatically determined):   -->
<!--   		v1.3.1.1                                                  -->
<!--   		v1.4.0.0                                                  -->
<!--   All objects are implicitly supported.                              -->
<!--  The following new v1.4 objects are passed through unchanged:        -->
<!--   	aggregate                                                         -->
<!--   	report                                                            -->
<!--   	attachment                                                        -->
<!--   	changeLog                                                         -->
<!--   	coordinateReferenceSystem                                         -->
<!--   	drillReport                                                       -->
<!-- ==================================================================== -->


<!-- ==================================================================== -->
<!-- History
	Initial release with v1.4.0 draft
	15October2008, 
		Added support new values of TypeSurveyTool.
		For backward transform added exclusion of the following: 
			calcAlgorithm 
			infieldRefCorUsed 
			interpolatedInfieldRefCorUsed 
			inHoleRefCorUsed 
			axialMagInterferenceCorUsed 
			bhaSagCorUsed
		Renamed IndexOffset to curveSensorsAligned.
	31october2008,
		Removed support for new values of TypeSurveyTool.
		Fixed test for adding a commemt about a deleted element by testing $keep against uppercase NO.
		For forward transform, added excusion of nullValue when parent is blockInfo.
		Renamed bhaSagCorUsed to cosagCorUsed.
		For backward transform, added exclusion of the following:
			MSACorUsed
			magTran1MSACor
			magTran2MSACor
			magAxialMSACor
		For backward transform, exclude uid from event and securityInformation.
		For deleted elements, capture all attributes in the generated comment.
		Added single-quote around deleted values in appinfo.
		Added support new values of QualifierType.
	03december2008
		For forward transform:
			Removed excusion of nullValue when parent is blockInfo.
			Copy realtime.dataGroup to itself and to commonData.serviceCategory.
		For backward transform:
			Create realtime.dataGroup from itself or from commonData.serviceCategory
			and create warning comment if both are given but are not equal.
			Add exclusion for extensionNameValue and extensionAny.
		Change 140 namespace to "http://www.witsml.org/schemas/1series".
		
-->
<!-- ==================================================================== -->

<!-- Input parameters. -->

	<!-- Path (without the trailing slash) to the folder containing the schema xsd files for the 'to' namespace. 
		This will be added to the schemaLocation in output XML file. 
		The default is the 'to' namespace. -->
	<xsl:param name="schemaLocationPath"></xsl:param>

	<!-- The time zone when v131 is the "from" schema (i.e., for forward conversions). -->
	<!-- Timestamp values which do not have a time zone will be modified to  have this value.-->
	<!-- Must be of the form "Z" or "+hh.mm" or "-hh.mm" (not checked). -->
	<!-- USE WITH CARE! Probably only useful with a known server or client that always uses local time. -->
	<xsl:param name="v131TimeZone"></xsl:param>



<!-- ============================================================== -->
<!-- This script assumes:
	1) The input file represents an XML file in the 'from' schema (based on its namespace).
	2) The root element is the plural object (i.e., with appended 's').
	3) All uom attributes are populated and unit conversion is not necessary.
	4) A program such as HTML Tidy will be run to indent the output (if desired).
	   A line break is generated after each element and at the beginning of each element container.
	5) Custom data can be copied in its same namespace.
	6) All v1.3.1.1 timestamp values have a timezone. See parameter "v131TimeZone" above.
-->

<!-- ============================================================== -->
<!-- Assumptions specific a FORWARD transform from v1.3.1.1 to v1.4.0

     Assumptions specific to the realtime object:
	1) The realtime.dataGroup value maps to commonData.serviceCategory.

     The following data will be lost.
	1) The @datum attribute in the following elements:
		mdDelta
		tvdDelta
		mdWater
		waterDepth
-->

<!-- ==================================================================== -->
<!-- Assumptions specific to a BACKWARD transform from v1.4.0 to v1.3.1.1.

     Assumptions specific to the realtime object:
	1) The commonData.serviceCategory value maps to realtime.dataGroup.

     The following data will be lost when converting from v1.4 to v1.3.1.1.
	 1) All new v1.4 elements and attributes (except serviceCategory).
	    A comment will be created for each deleted item. 
	    This includes the following:
		extensionNameValue
		extensionAny
		mdBitCurrent
		tvdBitCurrent
		dataDelimiter
		dataGroup           (parent element!=realtime)
		serviceCategory
		acquisitionTimeZone
		classIndex
		curveSensorsAligned
		dTimHeaderLastChanged
		codeMfg
		mudClass
		proprietaryCode
		stateDetailActivity
		depthRegistrationData
		magneticDeclination
		gridConvergence
		mapProjectionCRS
		geodeticCRS
		datumCRS
		horizontalLocation
		wellPublicLandSurveySystemLocation
		eventType
		isActive            (parent element=wellbore)
		tvd                 (parent element=fluid)
		presBopRating       (parent element=fluid)
		md                  (parent element=activity)
		tvd                 (parent element=activity)
		@uid		    (parent element=bitRecord)
		@uid		    (parent element=event)
		@uid		    (parent element=securityInformation)
-->


<!-- Global variables. -->

	<!-- relative versions. -->
	<xsl:variable name="oldVersion">http://www.witsml.org/schemas/131</xsl:variable>
	<xsl:variable name="newVersion">http://www.witsml.org/schemas/1series</xsl:variable>

	<!-- Namespace for the new schema. -->
	<xsl:variable name="direction">
		<xsl:for-each select="/child::*">
			<xsl:choose>
				<xsl:when test="namespace-uri() = $oldVersion">forward</xsl:when>
				<xsl:when test="namespace-uri() = $newVersion">backward</xsl:when>
				<xsl:otherwise>UNKNOWN</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>
	</xsl:variable>

	<!-- Namespace for the new schema. -->
	<xsl:variable name="newNameSpace">
		<xsl:choose>
			<xsl:when test="$direction='forward'" ><xsl:value-of select="$newVersion"/></xsl:when>
			<xsl:when test="$direction='backward'"><xsl:value-of select="$oldVersion"/></xsl:when>
			<xsl:otherwise>UNKNOWN</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

	<!-- The name of the singular output object. -->
	<xsl:variable name="object">
		<xsl:value-of  select="substring(name(.//child::*),1,string-length(name(.//child::*))-1)"/>
	</xsl:variable>

	<!-- version of the new schema. -->
	<xsl:variable name="version">
		<xsl:choose>
			<xsl:when test="$direction='forward'" >1.4.0.0</xsl:when>
			<xsl:when test="$direction='backward'">1.3.1.1</xsl:when>
			<xsl:otherwise>UNKNOWN</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

	<!-- schemaLocation of the new schema. -->
	<xsl:variable name="schemaLocation">
		<xsl:value-of select="$newNameSpace"/>
		<xsl:text> </xsl:text>
		<xsl:choose>
			<xsl:when test="$schemaLocationPath!=''">
				<xsl:value-of select="translate($schemaLocationPath,'\','/')"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$newNameSpace"/>
			</xsl:otherwise>
		</xsl:choose>
		<xsl:text>/obj_</xsl:text>
		<xsl:value-of select="$object"/>
		<xsl:text>.xsd</xsl:text>
	</xsl:variable>



<!-- Start here. -->
<xsl:template match="/" >
	<xsl:choose>
		<xsl:when test="$direction='backward' and $object='aggregate'">
			<!-- This object does not exist in the old version. Copy as is. -->
			<xsl:copy-of select="/child::* | comment()"/>
		</xsl:when>
		<xsl:when test="$direction='backward' and $object='report'">
			<!-- This object does not exist in the old version. Copy as is. -->
			<xsl:copy-of select="/child::* | comment()"/>
		</xsl:when>
		<xsl:when test="$direction='backward' and $object='attachment'">
			<!-- This object does not exist in the old version. Copy as is. -->
			<xsl:copy-of select="/child::* | comment()"/>
		</xsl:when>
		<xsl:when test="$direction='backward' and $object='changeLog'">
			<!-- This object does not exist in the old version. Copy as is. -->
			<xsl:copy-of select="/child::* | comment()"/>
		</xsl:when>
		<xsl:when test="$direction='backward' and $object='coordinateReferenceSystem'">
			<!-- This object does not exist in the old version. Copy as is. -->
			<xsl:copy-of select="/child::* | comment()"/>
		</xsl:when>
		<xsl:when test="$direction='backward' and $object='drillReport'">
			<!-- This object does not exist in the old version. Copy as is. -->
			<xsl:copy-of select="/child::* | comment()"/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:apply-templates select="/child::*"  mode="start"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>


<!-- Output one plural container per input. -->
<xsl:template match="*" mode="start">
	<xsl:call-template name="linebreak"/>
	<xsl:for-each select="parent::*">
		<xsl:call-template name="copy-comment"/>
	</xsl:for-each>
	<!-- The direction of conversion. -->
	<xsl:element name="{$object}s" namespace="{$newNameSpace}">
		<xsl:attribute name="xsi:schemaLocation"><xsl:value-of select="$schemaLocation"/></xsl:attribute>
		<xsl:attribute name="version"><xsl:value-of select="$version"/></xsl:attribute>
		<xsl:call-template name="copy-comment"/>
		<xsl:choose>
			<xsl:when test="$direction = 'forward'">
				<xsl:for-each select="./*">
					<xsl:choose>
						<xsl:when test="local-name(.)='documentInfo'">
							<xsl:apply-templates select="."                 mode="documentInfo-Forward"/>
						</xsl:when>
						<xsl:otherwise>
							<xsl:apply-templates select="."                 mode="copy-Forward"/>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:for-each>
			</xsl:when>
			<xsl:when test="$direction = 'backward'">
				<xsl:for-each select="./*">
					<xsl:choose>
						<xsl:when test="local-name(.)='documentInfo'">
							<xsl:apply-templates select="."                 mode="documentInfo-Backward"/>
						</xsl:when>
						<xsl:otherwise>
							<xsl:apply-templates select="."                 mode="copy-Backward"/>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:for-each>
			</xsl:when>
			<xsl:otherwise>ERROR-UNKNOWN-VERSION</xsl:otherwise>
		</xsl:choose>
	</xsl:element>
</xsl:template>

<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!--                        Templates for FORWARD OBJECT conversion.                          -->
<!--                       These templates are direction specific.                            -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->

<xsl:template match="*" mode="copy-Forward">
	<!-- Copies the text and attribute content of an element and all sub-elements into a new namespace. --> 
	<!-- This copies the whole hierarchy into a new namespace. -->
	<xsl:variable name="elementName"><xsl:value-of select="local-name(.)"/></xsl:variable>
	<xsl:variable name="parentName"><xsl:value-of select="local-name(./parent::*)"/></xsl:variable>
	<xsl:variable name="modifyDateTime">
		<xsl:choose>
			<xsl:when test="$v131TimeZone!=''">
				<xsl:choose>
					<xsl:when test="starts-with($elementName,'dTim')">YES</xsl:when>
					<xsl:when test="$elementName='startDateTimeIndex'">YES</xsl:when>
					<xsl:when test="$elementName='endDateTimeIndex'">YES</xsl:when>
					<xsl:when test="$elementName='maxDateTimeIndex'">YES</xsl:when>
					<xsl:when test="$elementName='minDateTimeIndex'">YES</xsl:when>
					<xsl:when test="$elementName='chromIntRpt'">YES</xsl:when>
					<xsl:when test="$elementName='creationDate'">YES</xsl:when>
					<xsl:when test="$elementName='installationDate'">YES</xsl:when>
					<xsl:when test="$elementName='lastAbandonDrill'">YES</xsl:when>
					<xsl:when test="$elementName='lastBopDrill'">YES</xsl:when>
					<xsl:when test="$elementName='lastBopPresTest'">YES</xsl:when>
					<xsl:when test="$elementName='lastCsgPresTest'">YES</xsl:when>
					<xsl:when test="$elementName='lastDiverterDrill'">YES</xsl:when>
					<xsl:when test="$elementName='lastFireBoatDrill'">YES</xsl:when>
					<xsl:when test="$elementName='lastRigInspection'">YES</xsl:when>
					<xsl:when test="$elementName='lastSafetyInspection'">YES</xsl:when>
					<xsl:when test="$elementName='lastSafetyMeeting'">YES</xsl:when>
					<xsl:when test="$elementName='lastTripDrill'">YES</xsl:when>
					<xsl:when test="$elementName='nextBopPresTest'">YES</xsl:when>
					<xsl:otherwise>NO</xsl:otherwise>
				</xsl:choose>
			</xsl:when>
			<xsl:otherwise>NO</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	<xsl:variable name="keep">
		<!-- Do we want to keep this element. That is, does it exist in the newer version. -->
		<xsl:text>YES</xsl:text>
	</xsl:variable>
	<xsl:variable name="dropDatum">
		<!-- Does this element contain a datum attribute that should be dropped. -->
		<xsl:choose>
			<xsl:when test="$elementName='mdDelta'">YES</xsl:when>
			<xsl:when test="$elementName='tvdDelta'">YES</xsl:when>
			<xsl:when test="$elementName='mdWater'">YES</xsl:when>
			<xsl:when test="$elementName='waterDepth'">YES</xsl:when>
			<xsl:otherwise>NO</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	<xsl:if test="$modifyDateTime='YES'">
		<!-- Add a comment if we will do something within the element creation. -->
		<xsl:variable name="TIME"><xsl:value-of select="substring-after(.,'T')"/></xsl:variable>
		<xsl:if test="contains(.,'T') and not(contains($TIME,'Z') or contains($TIME,'+') or contains($TIME,'-'))">
			<xsl:comment>ADDED: timezone='<xsl:value-of select="$v131TimeZone"/>' to-element='<xsl:value-of select="$elementName"/>'</xsl:comment>
		</xsl:if>
	</xsl:if>
	<xsl:if test="./@datum and $dropDatum='YES'">
		<!-- Add a comment if we will not do something within the element creation. -->
		<xsl:comment>DELETED: @datum='<xsl:value-of select="./@datum"/>' from-element='<xsl:value-of select="$elementName"/>'</xsl:comment>
	</xsl:if>
	<xsl:choose>
		<xsl:when test="$keep='NO'">
			<!-- Add a comment if we will not create the element. -->
			<xsl:variable name="attValue">
				<xsl:for-each select="@*">
					<xsl:value-of select="concat(' @',local-name(.),'=','''',.,'''')"/>
				</xsl:for-each>
				<xsl:value-of select="concat(' from-parent=''',$parentName,'''')"/>
			</xsl:variable>
			<xsl:comment>DELETED: <xsl:value-of select="concat($elementName,'=','''',.,'''')"/><xsl:value-of select="$attValue"/></xsl:comment>
		</xsl:when>
		<xsl:otherwise>
			<xsl:element name="{$elementName}" namespace="{$newNameSpace}">
				<xsl:choose>
					<xsl:when test="$modifyDateTime='YES'">
						<!-- This is a timestamp and we need to check for a timezone. -->
						<xsl:apply-templates select="."  mode="timestamp-Forward"/>
					</xsl:when>
					<xsl:when test="$elementName='objectGrowing'">
						<!-- Convert boolean to enum. -->
						<xsl:apply-templates select="."  mode="objectGrowing-Forward"/>
					</xsl:when>
					<xsl:when test="$elementName='classWitsml'">
						<!-- Possibly change a value. -->
						<xsl:apply-templates select="."  mode="copy-RealtimeData-Forward"/>
					</xsl:when>
					<xsl:when test="$elementName='commonData'">
						<xsl:apply-templates select="."  mode="commonData-Forward"/>
					</xsl:when>
					<xsl:when test="$elementName='customData'">
						<!-- Copy all children in the specified namespace. -->
						<xsl:copy-of select="* | text() | @* | comment()"/>
					</xsl:when>
					<xsl:when test="$dropDatum='YES'">
						<!-- Do not copy the datum attribute. -->
						<xsl:apply-templates select="."  mode="copy-value-uom"/>
					</xsl:when>
					<xsl:otherwise>
						<!-- Copy children in new namespace. -->
						<xsl:for-each select="./@*">
							<xsl:attribute name="{name(.)}"><xsl:value-of select="."/></xsl:attribute>
						</xsl:for-each>
						<xsl:if test="./child::*">
							<xsl:call-template name="linebreak"/>
						</xsl:if>
					<!-- Copy the content of this element either as text or as more element content. -->
						<xsl:apply-templates mode="copy-Forward"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:element>
			<xsl:call-template name="linebreak"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:template match="text()" mode="copy-Forward">
	<!-- Copies the text content of an element. --> 
	<xsl:value-of select="."/>
</xsl:template>

<xsl:template match="comment()" mode="copy-Forward">
	<!-- Copies the comment content. --> 
	<xsl:comment><xsl:value-of select="."/></xsl:comment>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="*" mode="objectGrowing-Forward">
	<!-- Convert boolean to enum value. -->
	<xsl:choose>
		<xsl:when test=".=''"></xsl:when>
		<xsl:when test=".='true' or .='1'">growing</xsl:when>
		<xsl:otherwise>closed</xsl:otherwise>
	</xsl:choose>
	<xsl:call-template name="copy-comment"/>
</xsl:template>

<xsl:template match="*" mode="copy-value-uom">
	<!-- Copy the element value and uom attribute. Any datum is not copied. -->
	<xsl:if test="./@uom">
		<xsl:attribute name="uom"><xsl:value-of select="./@uom"/></xsl:attribute>
	</xsl:if>
	<xsl:value-of select="."/>
	<xsl:call-template name="copy-comment"/>
</xsl:template>

<xsl:template match="*" mode="timestamp-Forward">
	<!-- Copy the timestamp and possibly add a timezone. -->
	<xsl:variable name="TIME"><xsl:value-of select="substring-after(.,'T')"/></xsl:variable>
	<xsl:choose>
		<xsl:when test="not(contains(.,'T')) or (contains($TIME,'Z') or contains($TIME,'+') or contains($TIME,'-'))">
			<!-- Either a time was not given or a timezone already exists. -->
			<xsl:value-of select="."/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="."/><xsl:value-of select="$v131TimeZone"/>
			<!-- Add a timezone. -->
		</xsl:otherwise>
	</xsl:choose>
	<xsl:call-template name="copy-comment"/>
</xsl:template>

<xsl:template match="*" mode="copy-RealtimeData-Forward">
	<!-- Copy the element value (possibly renamed). -->
	<xsl:choose>
		<xsl:when test=".='TVD of Bit'" >TVD of bit</xsl:when>
		<xsl:otherwise><xsl:value-of select="."/></xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:template match="*" mode="commonData-Forward">
	<!-- Copy the contents of commonData. -->
	<xsl:apply-templates select="w131:sourceName"                                mode="copy-element"/>
	<xsl:apply-templates select="w131:dTimCreation"                              mode="copy-timestamp-Forward"/>
	<xsl:apply-templates select="w131:dTimLastChange"                            mode="copy-timestamp-Forward"/>
	<xsl:apply-templates select="w131:itemState"                                 mode="copy-element"/>
	<!-- Presumes that the parent is realtime. Nothing will happen if it is not.--> 
	<xsl:apply-templates select="../w131:dataGroup"                              mode="serviceCategory-Forward"/>
	<xsl:apply-templates select="w131:comments"                                  mode="copy-element"/>
	<xsl:call-template name="copy-comment"/>
</xsl:template>

<xsl:template match="*" mode="copy-timestamp-Forward">
	<!-- Create an element with the same text content but with a different name and namespace. -->
	<!-- Any attributes will be ignored (i.e., not copied). --> 
	<!-- This should NOT be called for container elements. --> 
	<xsl:element name="{name(.)}" namespace="{$newNameSpace}">
		<xsl:apply-templates select="."                       mode="timestamp-Forward"/>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="*" mode="serviceCategory-Forward">
	<!-- Create an element for serviceCategory. --> 
	<xsl:comment>COPIED: serviceCategory from ../dataGroup.</xsl:comment>
	<xsl:element name="serviceCategory" namespace="{$newNameSpace}">
		<xsl:value-of select="."/>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>



<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!--                       Templates for BACKWARD OBJECT conversion.                          -->
<!--                       These templates are direction specific.                            -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->

<xsl:template match="*" mode="copy-Backward">
	<!-- Copies the text and attribute content of an element and all sub-elements into a new namespace. --> 
	<!-- This copies the whole hierarchy into a new namespace. -->
	<xsl:variable name="elementName"><xsl:value-of select="local-name(.)"/></xsl:variable>
	<xsl:variable name="parentName"><xsl:value-of select="local-name(./parent::*)"/></xsl:variable>
	<xsl:variable name="keep">
		<!-- Do we want to keep this element. That is, does it exist in the older version. -->
		<xsl:choose>
			<xsl:when test="$elementName='extensionNameValue'"/>
			<xsl:when test="$elementName='extensionAny'"/>
			<xsl:when test="$elementName='mdBitCurrent'"/>
			<xsl:when test="$elementName='tvdBitCurrent'"/>
			<xsl:when test="$elementName='dataDelimiter'"/>
			<xsl:when test="$elementName='dataGroup'            and $parentName!='realtime'"/>
			<xsl:when test="$elementName='serviceCategory'"/>
			<xsl:when test="$elementName='acquisitionTimeZone'"/>
			<xsl:when test="$elementName='classIndex'"/>
			<xsl:when test="$elementName='curveSensorsAligned'"/>
			<xsl:when test="$elementName='codeMfg'"/>
			<xsl:when test="$elementName='mudClass'"/>
			<xsl:when test="$elementName='proprietaryCode'"/>
			<xsl:when test="$elementName='stateDetailActivity'"/>
			<xsl:when test="$elementName='depthRegistrationData'"/>
			<xsl:when test="$elementName='calcAlgorithm'"/>
			<xsl:when test="$elementName='infieldRefCorUsed'"/>
			<xsl:when test="$elementName='interpolatedInfieldRefCorUsed'"/>
			<xsl:when test="$elementName='inHoleRefCorUsed'"/>
			<xsl:when test="$elementName='axialMagInterferenceCorUsed'"/>
			<xsl:when test="$elementName='cosagCorUsed'"/>
			<xsl:when test="$elementName='MSACorUsed'"/>
			<xsl:when test="$elementName='magTran1MSACor'"/>
			<xsl:when test="$elementName='magTran2MSACor'"/>
			<xsl:when test="$elementName='magAxialMSACor'"/>
			<xsl:when test="$elementName='magneticDeclination'"/>
			<xsl:when test="$elementName='gridConvergence'"/>
			<xsl:when test="$elementName='mapProjectionCRS'"/>
			<xsl:when test="$elementName='geodeticCRS'"/>
			<xsl:when test="$elementName='datumCRS'"/>
			<xsl:when test="$elementName='horizontalLocation'"/>
			<xsl:when test="$elementName='wellPublicLandSurveySystemLocation'"/>
			<xsl:when test="$elementName='isActive'            and $parentName='wellbore'"/>
			<xsl:when test="$elementName='tvd'                 and $parentName='fluid'"/>
			<xsl:when test="$elementName='presBopRating'       and $parentName='fluid'"/>
			<xsl:when test="$elementName='md'                  and $parentName='activity'"/>
			<xsl:when test="$elementName='tvd'                 and $parentName='activity'"/>
			<xsl:otherwise>YES</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	<xsl:choose>
		<xsl:when test="$keep='YES'">
			<xsl:if test="@uid and $elementName='bitRecord'">
				<xsl:comment>DELETED: @uid='<xsl:value-of select="@uid"/>' from-element='<xsl:value-of select="$elementName"/>'</xsl:comment>
			</xsl:if>
			<xsl:element name="{$elementName}" namespace="{$newNameSpace}">
				<xsl:choose>
					<xsl:when test="$elementName='customData'">
						<!-- Copy all children in the specified namespace. -->
						<xsl:copy-of select="* | text() | @* | comment()"/>
					</xsl:when>
					<xsl:when test="$elementName='objectGrowing'">
						<!-- Convert boolean to enum. -->
						<xsl:apply-templates select="."  mode="objectGrowing-Backward"/>
					</xsl:when>
					<xsl:when test="$elementName='classWitsml'">
						<!-- Possibly change a value. -->
						<xsl:apply-templates select="."  mode="copy-RealtimeData-Backward"/>
					</xsl:when>
					<xsl:when test="$elementName='type' and $parentName='qualifier'">
						<!-- Possibly change a value. -->
						<xsl:apply-templates select="."  mode="copy-QualifierType-Backward"/>
					</xsl:when>
					<xsl:when test="$elementName='realtime'">
						<xsl:apply-templates select="."  mode="realtime-Backward"/>
					</xsl:when>
					<xsl:otherwise>
						<!-- Copy children in new namespace. -->
						<xsl:choose>
							<xsl:when test="$elementName='bitRecord'">
								<!-- Do not copy the uid attribute. -->
							</xsl:when>
							<xsl:otherwise>
								<xsl:for-each select="./@*">
									<xsl:attribute name="{name(.)}"><xsl:value-of select="."/></xsl:attribute>
								</xsl:for-each>
							</xsl:otherwise>
						</xsl:choose>
						<xsl:if test="./child::*">
							<xsl:call-template name="linebreak"/>
						</xsl:if>
					<!-- Copy the content of this element either as text or as more element content. -->
						<xsl:apply-templates mode="copy-Backward"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:element>
			<xsl:call-template name="linebreak"/> 
		</xsl:when>
		<xsl:otherwise>
			<xsl:variable name="attValue">
				<xsl:for-each select="@*">
					<xsl:value-of select="concat(' @',local-name(.),'=','''',.,'''')"/>
				</xsl:for-each>
				<xsl:value-of select="concat(' from-parent=''',$parentName,'''')"/>
			</xsl:variable>
			<xsl:comment>DELETED: <xsl:value-of select="concat($elementName,'=','''',.,'''')"/><xsl:value-of select="$attValue"/></xsl:comment>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:template match="text()" mode="copy-Backward">
	<!-- Copies the text content of an element. --> 
	<xsl:value-of select="."/>
</xsl:template>

<xsl:template match="comment()" mode="copy-Backward">
	<!-- Copies the comment content. --> 
	<xsl:comment><xsl:value-of select="."/></xsl:comment>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="*" mode="objectGrowing-Backward">
	<!-- Convert boolean to enum value. -->
	<xsl:choose>
		<xsl:when test=".=''"></xsl:when>
		<xsl:when test=".='growing'">true</xsl:when>
		<xsl:otherwise>false</xsl:otherwise>
	</xsl:choose>
	<xsl:call-template name="copy-comment"/>
</xsl:template>

<xsl:template match="*" mode="copy-QualifierType-Backward">
	<!-- Copy the element value (possibly renamed). -->
	<xsl:choose>
		<xsl:when test=".='anhydrite'">anhydritic</xsl:when>
		<xsl:when test=".='belemnites'">belemnitic</xsl:when>
		<xsl:when test=".='bioturbation'">bioturbated</xsl:when>
		<xsl:when test=".='bitumen'">bituminous</xsl:when>
		<xsl:when test=".='burrows'">burrowed</xsl:when>
		<xsl:when test=".='calcite'">calcareous</xsl:when>
		<xsl:when test=".='calcite concretion'">calcite concr</xsl:when>
		<xsl:when test=".='chalk'">chalky</xsl:when>
		<xsl:when test=".='coal'">unknown</xsl:when>
		<xsl:when test=".='conglomerate'">conglomeratic</xsl:when>
		<xsl:when test=".='coral fragments'">coral</xsl:when>
		<xsl:when test=".='forams'">forams undifferentiated</xsl:when>
		<xsl:when test=".='fossil fragments'">fossil fragment</xsl:when>
		<xsl:when test=".='gilsonite'">unknown</xsl:when>
		<xsl:when test=".='gravel'">gravelly</xsl:when>
		<xsl:when test=".='gypsum'">gypsiferous</xsl:when>
		<xsl:when test=".='lithic fragments'">lithic fragment</xsl:when>
		<xsl:when test=".='marcasite'">unknown</xsl:when>
		<xsl:when test=".='marl'">marly</xsl:when>
		<xsl:when test=".='microfossils'">microfossil</xsl:when>
		<xsl:when test=".='oncoliths'">oncolithic</xsl:when>
		<xsl:when test=".='ooids'">ooid or oolith</xsl:when>
		<xsl:when test=".='pebble'">pebbly</xsl:when>
		<xsl:when test=".='pellets'">pelletal</xsl:when>
		<xsl:when test=".='peloids'">peloidal</xsl:when>
		<xsl:when test=".='pisoliths'">pisolith</xsl:when>
		<xsl:when test=".='rootlets'">unknown</xsl:when>
		<xsl:when test=".='salt'">salty</xsl:when>
		<xsl:when test=".='sand'">sandy</xsl:when>
		<xsl:when test=".='shell fragments'">shell</xsl:when>
		<xsl:when test=".='silt'">silty</xsl:when>
		<xsl:when test=".='spicules'">spicule</xsl:when>
		<xsl:when test=".='stylolites'">stylolitic</xsl:when>
		<xsl:when test=".='tuff'">tuffaceous</xsl:when>
		<xsl:otherwise><xsl:value-of select="."/></xsl:otherwise>
	</xsl:choose>
	<xsl:call-template name="copy-comment"/>
</xsl:template>

<xsl:template match="*" mode="copy-RealtimeData-Backward">
	<!-- Copy the element value (possibly renamed). -->
	<xsl:choose>
		<xsl:when test=".='TVD of bit'" >TVD of Bit</xsl:when>
		<xsl:otherwise><xsl:value-of select="."/></xsl:otherwise>
	</xsl:choose>
	<xsl:call-template name="copy-comment"/>
</xsl:template>

<xsl:template match="*" mode="realtime-Backward">
	<!-- Copy the contents of realtime. -->
	<xsl:for-each select="./@*">
		<xsl:attribute name="{name(.)}"><xsl:value-of select="."/></xsl:attribute>
	</xsl:for-each>
	<xsl:call-template name="copy-comment"/>
	<xsl:apply-templates select="w140:dTim"                                      mode="copy-element"/>
	<xsl:apply-templates select="w140:md"                                        mode="copy-element-with-attribute"/>
	<xsl:apply-templates select="w140:sequence"                                  mode="copy-element"/>
	<xsl:if test="w140:dTimHeaderLastChanged">
		<xsl:comment>DELETED: dTimHeaderLastChanged='<xsl:value-of select="w140:dTimHeaderLastChanged"/>' from-parent='realtime'</xsl:comment>
	</xsl:if>
	<xsl:apply-templates select="w140:activityCode"                              mode="copy-element"/>
	<xsl:apply-templates select="w140:detailActivity"                            mode="copy-element"/>
	<xsl:choose>
		<xsl:when test="w140:dataGroup!=''">
			<xsl:apply-templates select="w140:dataGroup"                 mode="copy-element"/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:apply-templates select="./w140:commonData/w140:serviceCategory"         mode="dataGroup-Backward"/>
		</xsl:otherwise>
	</xsl:choose>
	<xsl:if test="w140:dataGroup!='' and 
		      ./w140:commonData/w140:serviceCategory!='' and 
		      ./w140:commonData/w140:serviceCategory!=w140:dataGroup">
		<xsl:comment>WARNING: dataGroup does not equal ./commonData/serviceCategory.</xsl:comment>
	</xsl:if>
	<xsl:apply-templates select="w140:realtimeHeader"                            mode="copy-Backward"/>
	<xsl:apply-templates select="w140:channel"                                   mode="copy-Backward"/>
	<xsl:apply-templates select="w140:record"                                    mode="copy-Backward"/>
	<xsl:apply-templates select="w140:commonData"                                mode="copy-Backward"/>
	<xsl:apply-templates select="w140:customData"                                mode="copy-Backward"/>
	<xsl:call-template name="copy-comment"/>
</xsl:template>

<xsl:template match="*" mode="dataGroup-Backward">
	<!-- Create an element for dataGroup. --> 
	<xsl:comment>COPIED: dataGroup from ./commonData/serviceCategory.</xsl:comment>
	<xsl:element name="dataGroup" namespace="{$newNameSpace}">
		<xsl:value-of select="."/>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>


<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!--                    Templates for FORWARD DOCUMENT-INFO conversion.                       -->
<!--                       These templates are direction specific.                            -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->


<xsl:template match="w131:documentInfo" mode="documentInfo-Forward">
	<xsl:element name="{local-name(.)}" namespace="{$newNameSpace}">
		<xsl:call-template name="linebreak"/>
		<xsl:apply-templates select="w131:DocumentName"                      mode="rename-element-with-attribute">
			<xsl:with-param name="newName">documentName</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:DocumentAlias"                     mode="rename-element-with-attribute">
			<xsl:with-param name="newName">documentAlias</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:DocumentDate"                      mode="rename-timestamp-FWD">
			<xsl:with-param name="newName">documentDate</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:documentClass"                     mode="copy-element-with-attribute"/>
		<xsl:apply-templates select="w131:FileCreationInformation"           mode="cs_documentFileCreation-FWD"/>
		<xsl:apply-templates select="w131:SecurityInformation"               mode="cs_documentSecurityInfo-FWD"/>
		<xsl:apply-templates select="w131:Disclaimer"                        mode="rename-element">
			<xsl:with-param name="newName">disclaimer</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:AuditTrail"                        mode="cs_documentAudit-FWD"/>
		<xsl:apply-templates select="w131:Owner"                             mode="rename-element">
			<xsl:with-param name="newName">owner</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:Comment"                           mode="rename-element">
			<xsl:with-param name="newName">comment</xsl:with-param>
		</xsl:apply-templates>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="w131:FileCreationInformation" mode="cs_documentFileCreation-FWD">
	<xsl:element name="fileCreationInformation" namespace="{$newNameSpace}">
		<xsl:call-template name="linebreak"/>
		<xsl:apply-templates select="w131:FileCreationDate"                  mode="rename-timestamp-FWD">
			<xsl:with-param name="newName">fileCreationDate</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:SoftwareName"                      mode="rename-element">
			<xsl:with-param name="newName">softwareName</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:FileCreator"                       mode="rename-element">
			<xsl:with-param name="newName">fileCreator</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:Comment"                           mode="rename-element">
			<xsl:with-param name="newName">comment</xsl:with-param>
		</xsl:apply-templates>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="w131:SecurityInformation" mode="cs_documentSecurityInfo-FWD">
	<xsl:element name="securityInformation" namespace="{$newNameSpace}">
		<xsl:call-template name="linebreak"/>
		<xsl:apply-templates select="w131:Class"                             mode="rename-element">
			<xsl:with-param name="newName">class</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:System"                            mode="rename-element">
			<xsl:with-param name="newName">securitySystem</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:EndDate"                           mode="rename-timestamp-FWD">
			<xsl:with-param name="newName">endDate</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:Comment"                           mode="rename-element">
			<xsl:with-param name="newName">comment</xsl:with-param>
		</xsl:apply-templates>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="w131:AuditTrail" mode="cs_documentAudit-FWD">
	<xsl:element name="auditTrail" namespace="{$newNameSpace}">
		<xsl:call-template name="linebreak"/>
		<xsl:apply-templates select="w131:Event"                             mode="cs_documentEvent-FWD"/>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="w131:Event" mode="cs_documentEvent-FWD">
	<xsl:element name="event" namespace="{$newNameSpace}">
		<xsl:call-template name="linebreak"/>
		<xsl:apply-templates select="w131:EventDate"                         mode="rename-timestamp-FWD">
			<xsl:with-param name="newName">eventDate</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:ResponsibleParty"                  mode="rename-element">
			<xsl:with-param name="newName">responsibleParty</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w131:Comment"                           mode="rename-element">
			<xsl:with-param name="newName">comment</xsl:with-param>
		</xsl:apply-templates>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="*" mode="rename-timestamp-FWD">
	<!-- Create an element with the same text content but with a different name and namespace. -->
	<!-- Any attributes will be ignored (i.e., not copied). --> 
	<!-- This should NOT be called for container elements. --> 
	<xsl:param name="newName"/>
	<xsl:element name="{$newName}" namespace="{$newNameSpace}">
		<xsl:apply-templates select="."  mode="timestamp-Forward"/>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
	<xsl:variable name="TIME"><xsl:value-of select="substring-after(.,'T')"/></xsl:variable>
	<xsl:if test="contains(.,'T') and not(contains($TIME,'Z') or contains($TIME,'+') or contains($TIME,'-'))">
		<xsl:comment>ADDED: timezone='<xsl:value-of select="$v131TimeZone"/>' to-element=''<xsl:value-of select="$newName"/>'</xsl:comment>
	</xsl:if>
</xsl:template>


<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!--                   Templates for BACKWARD DOCUMENT-INFO conversion.                       -->
<!--                       These templates are direction specific.                            -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->

<xsl:template match="w140:documentInfo" mode="documentInfo-Backward">
	<xsl:element name="{local-name(.)}" namespace="{$newNameSpace}">
		<xsl:call-template name="linebreak"/>
		<xsl:apply-templates select="w140:documentName"                      mode="rename-element-with-attribute">
			<xsl:with-param name="newName">DocumentName</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:documentAlias"                     mode="rename-element-with-attribute">
			<xsl:with-param name="newName">DocumentAlias</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:documentDate"                      mode="rename-element">
			<xsl:with-param name="newName">DocumentDate</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:documentClass"                     mode="copy-element-with-attribute"/>
		<xsl:apply-templates select="w140:fileCreationInformation"           mode="cs_documentFileCreation-BWD"/>
		<xsl:apply-templates select="w140:securityInformation"               mode="cs_documentSecurityInfo-BWD"/>
		<xsl:apply-templates select="w140:disclaimer"                        mode="rename-element">
			<xsl:with-param name="newName">Disclaimer</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:auditTrail"                        mode="cs_documentAudit-BWD"/>
		<xsl:apply-templates select="w140:owner"                             mode="rename-element">
			<xsl:with-param name="newName">Owner</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:comment"                           mode="rename-element">
			<xsl:with-param name="newName">Comment</xsl:with-param>
		</xsl:apply-templates>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="w140:fileCreationInformation" mode="cs_documentFileCreation-BWD">
	<xsl:element name="FileCreationInformation" namespace="{$newNameSpace}">
		<xsl:call-template name="linebreak"/>
		<xsl:apply-templates select="w140:fileCreationDate"                  mode="rename-element">
			<xsl:with-param name="newName">FileCreationDate</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:softwareName"                      mode="rename-element">
			<xsl:with-param name="newName">SoftwareName</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:fileCreator"                       mode="rename-element">
			<xsl:with-param name="newName">FileCreator</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:comment"                           mode="rename-element">
			<xsl:with-param name="newName">Comment</xsl:with-param>
		</xsl:apply-templates>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="w140:securityInformation" mode="cs_documentSecurityInfo-BWD">
	<xsl:element name="SecurityInformation" namespace="{$newNameSpace}">
		<xsl:call-template name="linebreak"/>
		<xsl:if test="@uid">
			<xsl:comment>DELETED: @uid='<xsl:value-of select="@uid"/>' from-element='securityInformation'</xsl:comment>
		</xsl:if>
		<xsl:apply-templates select="w140:class"                             mode="rename-element">
			<xsl:with-param name="newName">Class</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:securitySystem"                    mode="rename-element">
			<xsl:with-param name="newName">System</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:endDate"                           mode="rename-element">
			<xsl:with-param name="newName">EndDate</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:comment"                           mode="rename-element">
			<xsl:with-param name="newName">Comment</xsl:with-param>
		</xsl:apply-templates>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="w140:auditTrail" mode="cs_documentAudit-BWD">
	<xsl:element name="AuditTrail" namespace="{$newNameSpace}">
		<xsl:call-template name="linebreak"/>
		<xsl:apply-templates select="w140:event"                             mode="cs_documentEvent-BWD"/>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="w140:event" mode="cs_documentEvent-BWD">
	<xsl:element name="Event" namespace="{$newNameSpace}">
		<xsl:call-template name="linebreak"/>
		<xsl:if test="@uid">
			<xsl:comment>DELETED: @uid='<xsl:value-of select="@uid"/>' from-element='event'</xsl:comment>
		</xsl:if>
		<xsl:apply-templates select="w140:eventDate"                         mode="rename-element">
			<xsl:with-param name="newName">EventDate</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:responsibleParty"                  mode="rename-element">
			<xsl:with-param name="newName">ResponsibleParty</xsl:with-param>
		</xsl:apply-templates>
		<xsl:apply-templates select="w140:comment"                           mode="rename-element">
			<xsl:with-param name="newName">Comment</xsl:with-param>
		</xsl:apply-templates>
		<xsl:if test="w140:eventType">
			<xsl:comment>DELETED: eventType='<xsl:value-of select="w140:eventType"/>' from-parent='event'</xsl:comment>
		</xsl:if>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>



<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!--               These templates are NOT specific to any one object.                        -->
<!--                  These templates are independent of direction.                           -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->
<!-- //////////////////////////////////////////////////////////////////////////////////////// -->




<xsl:template name="linebreak">
	<!-- Inserts a line break. -->
	<xsl:text>
</xsl:text>
</xsl:template>

<xsl:template name="copy-comment">
	<!-- Copies the child comments of the current node. --> 
	<xsl:apply-templates select="./child::comment()" mode="copy-all"/>
</xsl:template>


<xsl:template match="comment()" mode="copy-all">
	<!-- Copies the comment content. --> 
	<xsl:comment><xsl:value-of select="."/></xsl:comment>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="*" mode="copy-element">
	<!-- Create an element with the same name and text content but with a new namespace. -->
	<!-- Any attributes will be ignored. --> 
	<!-- This should NOT be called for container elements. -->
	<xsl:element name="{name(.)}" namespace="{$newNameSpace}">
		<xsl:value-of select="."/>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="*" mode="copy-element-with-attribute">
	<!-- Create an element with the same name and text content but with a new namespace. -->
	<!-- Any attributes will be copied. --> 
	<!-- This should NOT be called for container elements. -->
	<xsl:element name="{name(.)}" namespace="{$newNameSpace}">
		<xsl:for-each select="./@*">
			<xsl:attribute name="{name(.)}"><xsl:value-of select="."/></xsl:attribute>
		</xsl:for-each>
		<xsl:value-of select="."/>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="*" mode="rename-element">
	<!-- Create an element with the same text content but with a different name and namespace. -->
	<!-- Any attributes will be ignored (i.e., not copied). --> 
	<!-- This should NOT be called for container elements. --> 
	<xsl:param name="newName"/>
	<xsl:element name="{$newName}" namespace="{$newNameSpace}">
		<xsl:value-of select="."/>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>

<xsl:template match="*" mode="rename-element-with-attribute">
	<!-- Create an element with the same text content but with a different name and namespace. -->
	<!-- Any attributes will be copied. --> 
	<!-- This should NOT be called for container elements. --> 
	<xsl:param name="newName"/>
	<xsl:element name="{$newName}" namespace="{$newNameSpace}">
		<xsl:for-each select="./@*">
			<xsl:attribute name="{name(.)}"><xsl:value-of select="."/></xsl:attribute>
		</xsl:for-each>
		<xsl:value-of select="."/>
		<xsl:call-template name="copy-comment"/>
	</xsl:element>
	<xsl:call-template name="linebreak"/>
</xsl:template>


</xsl:transform>
