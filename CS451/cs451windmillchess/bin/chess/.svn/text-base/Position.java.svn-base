package chess;

import java.io.Serializable;

public class Position implements Serializable
{
	private static final long serialVersionUID = 3325195622135563816L;
	private int cellNumber;

	public Position(int cellNumber)
	{
		this.cellNumber = cellNumber;
	}

	public int getFile()
	{
		return cellNumber % 8;
	}

	public int getRank()
	{
		return cellNumber / 8;
	}

	public boolean equals(Position p)
	{
		return (p.getFile() == this.getFile() && p.getRank() == this.getRank());
	}

	public static char fileCharFromInt(int file)
	{
		return (char) (file + 97);
	}

	public int getCellNumber()
	{
		return this.cellNumber;
	}
}
