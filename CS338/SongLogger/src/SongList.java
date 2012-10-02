/*
 * Dustin Ingram
 * dustin@drexel.edu
 * CS338:GUI, Assignment #1
 */

import java.util.*;

class SongList
{
	private ArrayList<Song> songList;
	
	public SongList() {
		songList = new ArrayList<Song>();
	}

	public ArrayList<Song> getSongList() {
		return songList;
	}
	
	public Vector<String> getListData() {
		Vector<String> listData = new Vector<String>();
		for(int i=0; i<songList.size(); i++){
			String elementString = "<html>";
			elementString += songList.get(i).artistField +
			", \"" + songList.get(i).songtitleField + "\"" +
			", <i>" + songList.get(i).albumtitleField + "</i>" +
			", " + songList.get(i).tracknumberField + 
			", " + songList.get(i).lengthField;
			
			if (!songList.get(i).recordingyearField.equals(""))
				elementString += ", " + songList.get(i).recordingyearField;
			if (!songList.get(i).composerField.equals(""))
				elementString += ", " + songList.get(i).composerField;
			if (!songList.get(i).compositionyearField.equals(""))
				elementString += ", " + songList.get(i).compositionyearField;
			listData.addElement(elementString);
		}
		return listData;
	}

	public void add(Song addSong) {
		Song tmpSong = new Song();
		tmpSong.genre = addSong.genre;
		tmpSong.artistField = addSong.artistField;
		tmpSong.songtitleField = addSong.songtitleField;
		tmpSong.albumtitleField = addSong.albumtitleField;
		tmpSong.tracknumberField = addSong.tracknumberField;
		tmpSong.lengthField = addSong.lengthField;
		tmpSong.recordingyearField = addSong.recordingyearField;
		tmpSong.composerField = addSong.composerField;
		tmpSong.compositionyearField = addSong.compositionyearField;
		
		songList.add(tmpSong);			
	}

	public void remove(int selectedIndex) {
		songList.remove(selectedIndex);
	}		
}
