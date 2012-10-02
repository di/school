import static java.lang.Math.*;

public class SpokeModel {
        
    private int numSpokes;
	private double erdInput;
	private double osbInput;
	private double wlInput;
	private double wrInput;
	private double dlInput;
	private double drInput;
	private double cInput;

	private ComponentList rimList;
	private ComponentList hubList;
	
	private double leftOutput;
	private double rightOutput;	

	String[] spokeCombos = { "40", "36", "32", "28", "24", "20", "16" };
    
    SpokeModel() {
        reset();
    }
    
    public void reset() {
    	numSpokes = 0;
    	erdInput = 0;
    	osbInput = 0;
    	wlInput = 0;
    	wrInput = 0;
    	dlInput = 0;
    	drInput = 0;
    	cInput = 0;
    	
    	rimList = new ComponentList("rims.csv");
    	hubList = new ComponentList("hubs.csv");
    }
    
    public void calculate() {
    	// Calculating
    	leftOutput = sqrt(pow(dlInput/2*sin(2*PI*cInput/(numSpokes/2)),2)+pow(erdInput/2-((dlInput/2)*cos(2*PI*cInput/(numSpokes/2))),2)+pow(wlInput,2));
    	rightOutput = sqrt(pow(drInput/2*sin(2*PI*cInput/(numSpokes/2)),2)+pow(erdInput/2-((drInput/2)*cos(2*PI*cInput/(numSpokes/2))),2)+pow(wrInput,2));
    	
    	//Rounding    	
    	leftOutput = round(leftOutput * 100.0)/100.0;
    	rightOutput = round(rightOutput * 100.0)/100.0;
    }
    
    public void update(int numSpokes, double erdInput, double osbInput, double wlInput, double wrInput, double dlInput, double drInput, double cInput) {
    	if (numSpokes >= 0){
    		this.numSpokes = numSpokes;
    	}
    	if (erdInput >= 0){
    		this.erdInput = erdInput;
    	}
    	if (osbInput >= 0){
    		this.osbInput = osbInput;
    	}
    	if (wlInput >= 0){
    		this.wlInput = wlInput;
    	}
    	if (wrInput >= 0){
    		this.wrInput = wrInput;
    	}
    	if (dlInput >= 0){
    		this.dlInput = dlInput;
    	}
    	if (drInput >= 0){
    		this.drInput = drInput;
    	}
    	if (cInput >= 0){
    		this.cInput = cInput;
    	}    	
    }
    
	public double getCInput() {
		return cInput;
	}

	public void setCInput(double input) {
		cInput = input;
	}

	public double getDlInput() {
		return dlInput;
	}

	public void setDlInput(double dlInput) {
		this.dlInput = dlInput;
	}

	public double getDrInput() {
		return drInput;
	}

	public void setDrInput(double drInput) {
		this.drInput = drInput;
	}

	public double getErdInput() {
		return erdInput;
	}

	public void setErdInput(double erdInput) {
		this.erdInput = erdInput;
	}

	public double getLeftOutput() {
		return leftOutput;
	}

	public void setLeftOutput(double leftOutput) {
		this.leftOutput = leftOutput;
	}

	public double getOsbInput() {
		return osbInput;
	}

	public void setOsbInput(double osbInput) {
		this.osbInput = osbInput;
	}

	public double getRightOutput() {
		return rightOutput;
	}

	public void setRightOutput(double rightOutput) {
		this.rightOutput = rightOutput;
	}

	public int getNumSpokes() {
		return numSpokes;
	}

	public void setNumSpokes(int numSpokes) {
		this.numSpokes = numSpokes;
	}

	public double getWlInput() {
		return wlInput;
	}

	public void setWlInput(double wlInput) {
		this.wlInput = wlInput;
	}

	public double getWrInput() {
		return wrInput;
	}

	public void setWrInput(double wrInput) {
		this.wrInput = wrInput;
	}

	public String[] getSpokeCombos() {
		return spokeCombos;
	}

	public void setSpokeCombos(String[] spokeCombos) {
		this.spokeCombos = spokeCombos;
	}

	public ComponentList getRimList() {
		return rimList;
	}

	public void setRimList(ComponentList rimList) {
		this.rimList = rimList;
	}

	public ComponentList getHubList() {
		return hubList;
	}

	public void setHubList(ComponentList hubList) {
		this.hubList = hubList;
	}
}
