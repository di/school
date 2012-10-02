
public class Hub extends Component {

	private String name;
	private double dL;
	private double dR;
	private double WL;
	private double WR;
	
	public Hub(String name, double dL, double WL, double dR, double WR){
		this.name = name;
		this.dL = dL;
		this.dR = dR;
		this.WL = WL;
		this.WR = WR;
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
	public double getDL() {
		return dL;
	}
	public void setDL(double dl) {
		dL = dl;
	}
	public double getDR() {
		return dR;
	}
	public void setDR(double dr) {
		dR = dr;
	}
	public double getWL() {
		return WL;
	}
	public void setWL(double wl) {
		WL = wl;
	}
	public double getWR() {
		return WR;
	}
	public void setWR(double wr) {
		WR = wr;
	}

}
