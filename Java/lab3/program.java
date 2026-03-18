import java.util.*;
import java.io.File;
import java.io.InputStream;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
class Drawable
{
	private static int GetRandomNumber(int min, int max)
	{
		return (int) ((Math.random() * (max - min)) + min);
	}
	void draw(){};
	static class Shape
	{
		String shapeColor;
		double area;
		String getShapeColor()
		{
			return shapeColor;
		}
		double GetArea()
		{
			return area;
		}
		Shape(String color)
		{
			shapeColor=color;
		}
		void calcArea(){}
		public String toString()
		{
			return "Колір фігури: "+shapeColor+"; площа: "+String.format("%.2f", area);
		}
		
		public int compareTo(Shape figure)
		{
			return shapeColor.compareTo(figure.getShapeColor());
		}		
		
	}
	public static class AreaComparator implements Comparator<Shape>
	{
		public int compare(Shape figure1, Shape figure2)
		{
			double FirstArea=figure1.GetArea(),SecondArea=figure2.GetArea();
			if(FirstArea>SecondArea)
				return 1;
			else
				if(FirstArea<SecondArea)
					return -1;
				else
					return 0;
		}
	}
	static class Rectangle extends Shape
	{
		int width,length;
		Rectangle(int NewWidth,int NewLength,String color)
		{
			super(color);
			width=NewWidth;
			length=NewLength;
			calcArea();
		}
		void calcArea()
		{
			area=width*length;
		}
		//@Override
		public String toString()
		{
			return "ПРЯМОКУТНИК: колір: "+shapeColor+"; ширина: "+width+"; довжина: "+length+"; площа: "+String.format("%.2f", area);
		}
	}
	static class Triangle extends Shape
	{
		int side1,side2,side3;
		Triangle(int NewSide1,int NewSide2,int NewSide3,String color)
		{
			super(color);
			side1=NewSide1;
			side2=NewSide2;
			side3=NewSide3;
			calcArea();
		}
		void calcArea()
		{
			double HalfPerimeter=(side1+side2+side3)/2;
			double dif1,dif2,dif3;
			if(HalfPerimeter>side1)
				dif1=HalfPerimeter-side1;
			else
				dif1=side1-HalfPerimeter;
			if(HalfPerimeter>side2)
				dif2=HalfPerimeter-side2;
			else
				dif2=side2-HalfPerimeter;
			if(HalfPerimeter>side3)
				dif3=HalfPerimeter-side3;
			else
				dif3=side3-HalfPerimeter;
			area=Math.sqrt(HalfPerimeter*dif1*dif2*dif3);
		}
		public String toString()
		{
			return "ТРИКУТНИК: колір: "+shapeColor+"; сторона 1: "+side1+"; сторона 2: "+side2+"; сторона 3: "+side3+"; площа: "+String.format("%.2f", area);
		}
	}
	static class Circle extends Shape
	{
		int radius;		
		Circle(int NewRadius,String color)
		{
			super(color);
			radius=NewRadius;
			calcArea();
		}
		void calcArea()
		{
			area=Math.PI*Math.pow(radius,2);
		}
		public String toString()
		{
			return "КОЛО: колір: "+shapeColor+"; радіус: "+radius+"; площа: "+String.format("%.2f", area);
		}
		
	}
	public static void DisplayAllFigures(List<Shape> figures)
	{
		for(Shape figure : figures)
			System.out.println(figure);
	}
	public static void main(String args [])throws IOException
	{		
		String[] colors  = new String[] {"чорний","блакитний","сірий","зелений","червоний","білий","жовтий","фіолетовий","синій","оранжевый"};
		int i,CountOfFigures=20,ColorIndex,FigureNumber;
		double TotalArea=0,RectanglesArea=0,TrianglesArea=0,CirclesArea=0;
		//Shape[] figures=new Shape[CountOfFigures];
		List<Shape> figures = new ArrayList<>();
		for(i=0; i<CountOfFigures; i++)
		{
			FigureNumber=GetRandomNumber(0,3);
			switch(FigureNumber)
			{
				case 0: figures.add(new Rectangle(GetRandomNumber(5,20),GetRandomNumber(30,50),colors[GetRandomNumber(0,10)])); break;
				case 1: figures.add(new Triangle(GetRandomNumber(5,20),GetRandomNumber(30,50),GetRandomNumber(40,70),colors[GetRandomNumber(0,10)])); break;
				case 2: figures.add(new Circle(GetRandomNumber(20,100),colors[GetRandomNumber(0,10)])); break;
			}
		}
		DisplayAllFigures(figures);
		for(Shape figure : figures)
		{
			TotalArea+=figure.GetArea();
			if(figure.getClass()==Rectangle.class)
				RectanglesArea+=figure.area;
			else
				if(figure.getClass()==Triangle.class)
					TrianglesArea+=figure.area;
				else
					if(figure.getClass()==Circle.class)
						CirclesArea+=figure.area;
		}		
		System.out.println("--------------------------------\nПлоща всіх фігур: "+String.format("%.2f", TotalArea));
		System.out.println("Площа прямокутників: "+String.format("%.2f", RectanglesArea));
		System.out.println("Площа трикутників: "+String.format("%.2f", TrianglesArea));
		System.out.println("Площа кіл: "+String.format("%.2f", CirclesArea));		
		Comparator<Shape> CompareArea = new AreaComparator();
		Collections.sort(figures,CompareArea);
		System.out.println("------------------ВІДСОРТОВАНО ЗА ПЛОЩЕЮ:------------------");
		DisplayAllFigures(figures);
	}
}