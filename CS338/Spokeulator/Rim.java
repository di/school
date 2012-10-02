
public class Rim extends Component {

	private String name;
	private double erd;
	private double osb;
	
	public Rim(String name, double erd, double osb) {
		this.name = name;
		this.erd = erd;
		this.osb = osb;
	}
	
	public String toString() {
		return name;
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public double getErd() {
		return erd;
	}
	public void setErd(double erd) {
		this.erd = erd;
	}
	public double getOsb() {
		return osb;
	}
	public void setOsb(double osb) {
		this.osb = osb;
	}
	
}
