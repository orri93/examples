package gos.example.provider;

public class PersonProvider {
	private int id;
	private String firstName;
	private String lastName;
	private String mobilePhone;
	private String mailingAddress;
	private String zipCode;

	// Dummy constructor needed for rest invocation
	public PersonProvider() {

	}

	public PersonProvider(int id, String firstName, String lastName,
	    String mobilePhone, String mailingAddress, String zipCode) {
		this.id = id;
		this.firstName = firstName;
		this.lastName = lastName;
		this.mobilePhone = mobilePhone;
		this.mailingAddress = mailingAddress;
		this.zipCode = zipCode;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public String getMobilePhone() {
		return mobilePhone;
	}

	public void setMobilePhone(String mobilePhone) {
		this.mobilePhone = mobilePhone;
	}

	public String getMailingAddress() {
		return mailingAddress;
	}

	public void setMailingAddress(String mailingAddress) {
		this.mailingAddress = mailingAddress;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getZipCode() {
		return zipCode;
	}

	public void setZipCode(String zipCode) {
		this.zipCode = zipCode;
	}
}
