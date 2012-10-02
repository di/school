/*
 * Dustin Ingram
 * dustin@drexel.edu
 * CS338:GUI, Assignment #1
 */

public class Song {

	int genre;
	String artistField;
	String songtitleField;
	String albumtitleField;
	String tracknumberField;
	String lengthField;
	String recordingyearField;
	String composerField;
	String compositionyearField;

	public Song() {
		this.genre = 0;
		artistField = "";
		songtitleField = "";
		albumtitleField = "";
		tracknumberField = "";
		lengthField = "";
		recordingyearField = "";
		composerField = "";
		compositionyearField = "";		
	}

	public void print(String message) {
		System.out.println(message + "\n" +
				"\tArtist: " + this.artistField + "\n" +
				"\tSong Title: " + this.songtitleField + "\n" +
				"\tAlbum Title: " + this.albumtitleField + "\n" +
				"\tTrack Number: " + this.tracknumberField + "\n" +
				"\tTrack Length: " + this.lengthField + "\n" +
				"\tRecording Year: " + this.recordingyearField + "\n" +
				"\tComposer: " + this.composerField + "\n" +
				"\tComposition Year: " + this.compositionyearField + "\n"
				);		
	}

	public int getGenre() {
		return genre;
	}

	public void setGenre(int genre) {
		this.genre = genre;
	}
	
	
	public String getArtistField() {
		return artistField;
	}

	public void setArtistField(String artistField) {
		this.artistField = artistField;
	}

	public String getSongtitleField() {
		return songtitleField;
	}

	public void setSongtitleField(String songtitleField) {
		this.songtitleField = songtitleField;
	}

	public String getAlbumtitleField() {
		return albumtitleField;
	}

	public void setAlbumtitleField(String albumtitleField) {
		this.albumtitleField = albumtitleField;
	}

	public String getTracknumberField() {
		return tracknumberField;
	}

	public void setTracknumberField(String tracknumberField) {
		this.tracknumberField = tracknumberField;
	}

	public String getLengthField() {
		return lengthField;
	}

	public void setLengthField(String lengthField) {
		this.lengthField = lengthField;
	}

	public String getRecordingyearField() {
		return recordingyearField;
	}

	public void setRecordingyearField(String recordingyearField) {
		this.recordingyearField = recordingyearField;
	}

	public String getComposerField() {
		return composerField;
	}

	public void setComposerField(String composerField) {
		this.composerField = composerField;
	}

	public String getCompositionyearField() {
		return compositionyearField;
	}

	public void setCompositionyearField(String compositionyearField) {
		this.compositionyearField = compositionyearField;
	}

	public boolean isComplete() {

		if(this.artistField.equals("") ||
				this.songtitleField.equals("") ||
				this.albumtitleField.equals("") ||
				this.tracknumberField.equals("") ||
				this.lengthField.equals("")) {
			return false;
		}
		if(this.genre == 2 && this.composerField .equals("")) {
			return false;
		}
		
		return true;
	}
}
