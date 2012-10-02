import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.Vector;


public class ComponentList {

	private ArrayList<Component> componentList;
	
	public ComponentList(String filename) {
		componentList = new ArrayList<Component>();
		parse(filename);		
	}
	
	public void add(Component c){
		componentList.add(c);
	}
	
	public Vector<String> getJListData() {
		Vector<String> tmpList = new Vector<String>();
		for(int i=0; i<componentList.size(); i++){
			tmpList.add(i, componentList.get(i).toString());			
		}
		return tmpList;
	}
		
	public void parse(String filename){
		File file = new File(filename);
		 
		BufferedReader bufRdr;
		try {
			bufRdr = new BufferedReader(new FileReader(file));
		
			String line = bufRdr.readLine(); //eat first line
			while((line = bufRdr.readLine()) != null)
			{
				StringTokenizer st = new StringTokenizer(line,";");
				while (st.hasMoreTokens())
				{
					if (filename.equals("rims.csv")){
						componentList.add(new Rim(st.nextToken(), Double.parseDouble(st.nextToken()), Double.parseDouble(st.nextToken())));
					}
					else if (filename.equals("hubs.csv")){
						componentList.add(new Hub(st.nextToken(), Double.parseDouble(st.nextToken()), Double.parseDouble(st.nextToken()), Double.parseDouble(st.nextToken()), Double.parseDouble(st.nextToken())));
					}
					
				}
			}
			bufRdr.close(); 
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public Component get(int rimIndex) {
		return componentList.get(rimIndex);
	}
}
