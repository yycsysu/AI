import java.awt.*;
import java.awt.image.*;
import javax.imageio.*;
import javax.swing.*;
import java.io.*;
import java.math.*;
import java.util.*;

public class DisplayChart {
	private int[] x;
	private double[] y;
	private int[] my;
	private int count;

	DisplayChart() {
		x = new int[1000];
		y = new double[1000];
		my = new int[1000];
	}

	public static void main(String[] args) throws java.io.IOException {
		DisplayChart dc = new DisplayChart();
		int total = dc.count = dc.readData();
		/*for (int i = 0; i < dc.count; i++) {
			System.out.println(dc.x[i] + " " + dc.y[i] + " " + dc.my[i]);
		}*/
		BufferedImage img = new BufferedImage(450, 250, BufferedImage.TYPE_INT_RGB);
		dc.displayInChart(img);

		File fout = new File("chart.bmp");
		ImageIO.write(img, "bmp", fout);
	}

	public int readData() {
		int index = 0;
		int index2 = 500;

		try {
			FileReader fr1 = new FileReader("output1.txt");
			FileReader fr2 = new FileReader("output2.txt");

			BufferedReader br1 = new BufferedReader(fr1);
			BufferedReader br2 = new BufferedReader(fr2);

			String str = null;
			while((str = br1.readLine()) != null) {
				String[] strs = str.split(" ");
				x[index] = Integer.parseInt(strs[0]);
				y[index] = Double.valueOf(strs[1]);
				my[index] = (int)Math.round(y[index] * 1000) - 751;
				index++;
			}
			while((str = br2.readLine()) != null) {
				String[] strs = str.split(" ");
				x[index2] = Integer.parseInt(strs[0]);
				y[index2] = Double.valueOf(strs[1]);
				my[index2] = (int)Math.round(y[index2] * 1000) - 751;
				index2++;
			}
		} catch (IOException e) {
			System.out.println("File Read Error!");
		}
		return index;
	}

	public void displayInChart(BufferedImage img) {
		int width = img.getWidth();
		int height = img.getHeight();
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				img.setRGB(i, j, 0xffffffff);
			}
		}
		for (int i = 0; i < count - 1; i++) {
			img.setRGB(x[i], height - my[i], 0xff00ff00);
			int up = my[i] > my[i + 1] ? my[i] : my[i + 1];
			int down = my[i] < my[i + 1] ? my[i] : my[i + 1];
			for (int j = down; j < up; j++)
				img.setRGB(x[i], height - j, 0xff00ff00);
		}
		img.setRGB(x[count - 1], height - my[count - 1], 0xff00ff00);
		for (int i = 500; i < 499 + count; i++) {
			img.setRGB(x[i], height - my[i], 0xff0000ff);
			int up = my[i] > my[i + 1] ? my[i] : my[i + 1];
			int down = my[i] < my[i + 1] ? my[i] : my[i + 1];
			for (int j = down; j < up; j++)
				img.setRGB(x[i], height - j, 0xff0000ff);
		}
		img.setRGB(x[499 + count], height - my[499 + count], 0xff0000ff);
	}
}