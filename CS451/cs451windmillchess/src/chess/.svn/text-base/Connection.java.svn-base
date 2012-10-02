package chess;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.Enumeration;

public class Connection
{
	private ServerSocket listenSocket;
	private Socket comSocket;

	private ObjectOutputStream out;
	private ObjectInputStream in;

	public Connection(Socket established) throws IOException
	{
		comSocket = established;
		out = new ObjectOutputStream(comSocket.getOutputStream());
		in = new ObjectInputStream(comSocket.getInputStream());
	}

	public Connection(int listenPort) throws IOException
	{
		listenSocket = new ServerSocket(listenPort);
	}

	public void awaitConnection() throws IOException
	{
		if (listenSocket != null)
		{
			comSocket = listenSocket.accept();
			out = new ObjectOutputStream(comSocket.getOutputStream());
			in = new ObjectInputStream(comSocket.getInputStream());
		}
	}

	public boolean connectionEstablished()
	{
		return comSocket != null;
	}

	public void sendState(StateUpdate update) throws IOException
	{
		out.writeObject(new StateUpdate(update.getOldPosition(), update.getNewPosition()));
	}

	public StateUpdate awaitState() throws IOException, ClassNotFoundException
	{
		StateUpdate update = (StateUpdate) in.readObject();
		return update;
	}

	// convenience function to display network interfaces
	public static String getNetworkInfo()
	{
		String info = "<html><body>";

		try
		{
			// get the network interfaces
			Enumeration<NetworkInterface> interfaces = NetworkInterface.getNetworkInterfaces();

			while (interfaces.hasMoreElements())
			{
				NetworkInterface i = interfaces.nextElement();

				// if the interface is connected and no the loopback adapter
				if (i.isUp() && !i.isLoopback())
				{
					// get the ip addresses for this interface
					Enumeration<InetAddress> ips = i.getInetAddresses();

					// kind of a hacky way to shorten the display name
					info += "<b>" + i.getDisplayName().split("-")[0] + "</b>:\n";
					info += "<ul>";
					while (ips.hasMoreElements())
						info += "<li>" + ips.nextElement().toString() + "\n</li>";
					info += "</ul>";
				}
			}
			info += "</body></html>";

		} catch (SocketException e)
		{
			e.printStackTrace();
		}

		return info;
	}
}
