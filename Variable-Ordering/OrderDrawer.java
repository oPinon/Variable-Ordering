package forceOrdering;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

import javax.imageio.ImageIO;

public class OrderDrawer {

	static int nbVariables;
	static int charSize = 12;
	static int stringLength = 150; // in px
	static int width;
	static int height;
	static int margin;
	static int pointSize = charSize/3;
	static int strokeSize = charSize/4;
	static ArrayList<ArrayList<Integer>> hyperEdges = new ArrayList<ArrayList<Integer>>();
	static String[] names = new String[0];

	/**
	 * @param first param shall be the input file name
	 * second param can be output file name
	 */
	public static void main(String[] args) {
		
		// parsing file
		try {

			if(args.length<1) { System.err.println("enter the input filename as parameter"); System.exit(0);}
			File source = new File(args[0]);
			Scanner in = new Scanner(source);
			
			nbVariables = in.nextInt();
			margin = 2*charSize;
			
			height = charSize*nbVariables + 2*margin;
			width = height + 2*charSize+stringLength;
			
			names = new String[nbVariables];
			for(int i=0; i<nbVariables; i++) {
				names[i] = in.next();
			}
			
			while(in.hasNext()) {
				int toRead = in.nextInt();
				ArrayList<Integer> edge = new ArrayList<Integer>();
				for(int i=0; i<toRead; i++) {
					edge.add(in.nextInt());
				}
				hyperEdges.add(edge);
			}
			in.close();

		}
		catch (FileNotFoundException e) {
			System.err.println("cannot read file");
			System.exit(0);
		}
		
		// rendering
		BufferedImage toReturn = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		
		Graphics2D g = (Graphics2D) toReturn.getGraphics();
		g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		
		g.setColor(Color.black); // color background
		g.fillRect(0, 0, width, height);
		
		int rightStart = width-margin-stringLength-charSize;
		
		g.setColor(Color.white); // color variables' point
		for(int i=0; i<nbVariables; i++) {
			g.fillOval(rightStart, getY(i)+charSize/2, pointSize, pointSize);
			g.drawString(names[i], rightStart+charSize, getY(i)+charSize);
		}
		
		// draw HyperEdges
		g.setStroke(new BasicStroke(strokeSize,BasicStroke.CAP_ROUND,
		        BasicStroke.JOIN_BEVEL));
		for(int i=0; i<hyperEdges.size(); i++) {
			ArrayList<Integer> edge = hyperEdges.get(i);
			int barycenter = getBarycenter(edge);
			int xEdge = rightStart - charSize - getSpan(edge)*(rightStart-margin)*3/4/nbVariables;
			g.setColor(Color.white);
			g.drawString(" "+i, xEdge-2*charSize, getY(barycenter)+charSize/2);
			g.setColor(getColor(i));
			for(int j : edge) {
				g.drawLine(rightStart, getY(j)+charSize/2, xEdge, getY(barycenter)+charSize/2);
			}
		}
		
		g.dispose();
		
		String outputFile;
		if(args.length<2) { outputFile = "render.png"; }
		else { outputFile = args[1]; }
		try {
			ImageIO.write(toReturn, "png", new File(outputFile));
		} catch (IOException e) {
			System.err.println("couldn't write render image");
			System.exit(0);
		}
	}
	
	private static int getSpan(ArrayList<Integer> list) {
		int min = Integer.MAX_VALUE;
		int max = Integer.MIN_VALUE;
		for(int i : list) {
			if(i<min) { min = i; }
			if(i>max) { max = i; }
		}
		return max - min;
	}
	
	private static int getBarycenter(ArrayList<Integer> list) {
		int sum = 0;
		for(int i : list) { sum += i; }
		return sum/list.size();
	}
	
	private static Color getColor(int edgeRank) {
		if(edgeRank<hyperEdges.size()/3) {
			int i = (edgeRank*3*255)/hyperEdges.size();
			return new Color(i,255-i,255,100);
		}
		else if(edgeRank<hyperEdges.size()*2/3){
			int i = ((edgeRank-hyperEdges.size()/3)*255*3)/hyperEdges.size();
			return new Color(255,i,255-i,100);
		}
		else {
			int i = ((edgeRank-hyperEdges.size()*2/3)*255*3)/hyperEdges.size();
			return new Color(255-i,255,i,100);
		}
	}
	
	private static int getY(int pos) {
		return margin + ((height-2*margin)*pos)/nbVariables;
	}

}



