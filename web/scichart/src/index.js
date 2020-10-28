import {SciChartSurface} from "scichart/charting/Visuals/SciChartSurface";
import {NumericAxis} from "scichart/charting/Visuals/Axis/NumericAxis";
import {FastLineRenderableSeries} from "scichart/charting/visuals/RenderableSeries/FastLineRenderableSeries";
import {XyDataSeries} from "scichart/charting/Model/XyDataSeries";

async function initSciChart() {
    // Create the SciChartSurface in the div 'scichart-root'
    // The SciChartSurface, and webassembly context 'wasmContext' are paired. This wasmContext
    // instance must be passed to other types that exist on the same surface.
    const {sciChartSurface, wasmContext} = await SciChartSurface.create("scichart-root");
    // Create an X,Y Axis and add to the chart
    const xAxis = new NumericAxis(wasmContext);
    const yAxis = new NumericAxis(wasmContext);
   
    sciChartSurface.xAxes.add(xAxis);
    sciChartSurface.yAxes.add(yAxis);

    // Declare a DataSeries
    const xyDataSeries = new XyDataSeries(wasmContext);
    xyDataSeries.append(1, 2);
    xyDataSeries.append(3,4);
    // Add a line series to the SciChartSurface
    const lineSeries = new FastLineRenderableSeries(wasmContext);
    lineSeries.strokeThickness = 2;
    lineSeries.stroke = "rgba(255,0,0,1)";
    lineSeries.dataSeries = xyDataSeries;

    sciChartSurface.renderableSeries.add(lineSeries);

    // zoom to fit
    sciChartSurface.zoomExtents();
}
initSciChart();
