/*
 * Dustin Ingram
 * dustin@drexel.edu
 * CS338:GUI, Assignment #1
 */

import java.util.Vector;

public class InputManager {
	
	SongList songList;
	Song currentSong;
	
	public InputManager() {
		songList = new SongList();
		currentSong = new Song();
	}
	

	public void add() {
		if(currentSong.isComplete()) {
			songList.add(currentSong);	
		}
	}

	public void change() {
		// TODO Auto-generated method stub
		
	}

	public void remove(int selectedIndex) {
		songList.remove(selectedIndex);
		
	}
	
	public SongList getSongList()
	{
		return songList;
	}

	public void setGenre(int selectedIndex) {
		currentSong.genre = selectedIndex;
	}
	
	public int getGenre() {
		return currentSong.genre;		
	}
	
	public String getArtistField() {
		return currentSong.artistField;
	}


	public void setArtistField(String artistField) {
		currentSong.artistField = artistField;
	}


	public String getSongtitleField() {
		return currentSong.songtitleField;
	}


	public void setSongtitleField(String songtitleField) {
		currentSong.songtitleField = songtitleField;
	}


	public String getAlbumtitleField() {
		return currentSong.albumtitleField;
	}


	public void setAlbumtitleField(String albumtitleField) {
		currentSong.albumtitleField = albumtitleField;
	}


	public String getTracknumberField() {
		return currentSong.tracknumberField;
	}


	public void setTracknumberField(String tracknumberField) {
		currentSong.tracknumberField = tracknumberField;
	}


	public String getLengthField() {
		return currentSong.lengthField;
	}


	public void setLengthField(String lengthField) {
		currentSong.lengthField = lengthField;
	}


	public String getRecordingyearField() {
		return currentSong.recordingyearField;
	}


	public void setRecordingyearField(String recordingyearField) {
		currentSong.recordingyearField = recordingyearField;
	}


	public String getComposerField() {
		return currentSong.composerField;
	}


	public void setComposerField(String composerField) {
		currentSong.composerField = composerField;
	}


	public String getCompositionyearField() {
		return currentSong.compositionyearField;
	}


	public void setCompositionyearField(String compositionyearField) {
		currentSong.compositionyearField = compositionyearField;
	}


	public Vector getListData() {
		return songList.getListData();
	}


	public void clear() {
		currentSong = new Song();
	}


	public void setCurrentSong(Song song) {
		this.currentSong = song;
		
	}

}
