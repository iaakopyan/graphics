#include <graphics.h>

using namespace std;

class Point 
{
	public:
		double x, y, z;
		Point()
		{
			x = 0; y = 0; z = 0;
		}
		Point(double a, double b, double c)
		{
			x = a; y = b; z = c;
		}
};

class vertex 
{
	public:
		Point worldcoord;
		Point viewcoord;
		vertex(){};
		void vertex1(Point p)
		{
			worldcoord = p;
		}
		~vertex(){};
		void setviewpoint(Point cubecoord) 
		{
			double Ro = cubecoord.x, alp=cubecoord.y, fi=cubecoord.z;
			viewcoord.x = -worldcoord.x * sin(alp) + worldcoord.y * cos(alp); 
			viewcoord.y = -worldcoord.x * cos(fi) * cos(alp) - worldcoord.y * cos(fi) * sin(alp) + worldcoord.z * sin(fi); 
			viewcoord.z = -worldcoord.x * sin(fi) * cos(alp) - worldcoord.y * sin(fi) * sin(alp) - worldcoord.z * cos(fi) + Ro;
		}
};

class edge
{
	private:
		vertex startvertex, finishvertex; 
	public:
		edge(){}; 
		void edge1(vertex sv, vertex fv)
		{
			startvertex = sv;
			finishvertex = fv;
		}
		~edge(){};
		void drawedge(double d)
		{
			d = d/2; 
			double x1 = (int)((d*startvertex.viewcoord.x)/startvertex.viewcoord.z);
			double y1 = (int)((d*startvertex.viewcoord.y)/startvertex.viewcoord.z);
			double x2 = (int)((d*finishvertex.viewcoord.x)/finishvertex.viewcoord.z);
			double y2 = (int)((d*finishvertex.viewcoord.y)/finishvertex.viewcoord.z);
			line(x1+(getmaxx()/2), y1+(getmaxy()/2), x2+(getmaxx()/2), y2+(getmaxy()/2));
  		}
};

class newdot{
	public: 
		int a, b;
};

class Surface
{
	private:
		vertex *vlist; 
		edge *elist; 
		newdot *newdot1;
		Point viewPoint;
		bool flg = 0;
	public:
		int n, m;
		friend class edge;
		friend class vertex;
		void draw()
		{
			for (int i=0; i<m; i++)
				elist[i].drawedge(viewPoint.x);
		}
		void load()
		{
			int a, b, c;
			if(!flg)
			{
				FILE *f;
				f = fopen("lab3.dat", "r");
  				if (f != NULL) 
				{
					fscanf(f, "%d", &n); //
    				vlist = new vertex[n];
    				for (int i=0; i<n; i++)
					{
    					fscanf(f, "%d", &a);
    					fscanf(f, "%d", &b);
    					fscanf(f, "%d", &c);
    					Point p = Point(a*100, b*100, c*100);
						vlist[i].vertex1(p);
						vlist[i].setviewpoint(viewPoint);
					}
					fscanf(f, "%d", &m);
					elist = new edge[m];
					newdot1 = new newdot[m];
					for (int i=0; i<m; i++)
					{
						fscanf(f, "%d", &a);
    					fscanf(f, "%d", &b);
    					newdot1[i].a = a;
    					newdot1[i].b = b;
    					elist[i].edge1(vlist[newdot1[i].a], vlist[newdot1[i].b]);
					}
					flg = 1;
				}
			}
			for (int i=0; i<n; i++)
				vlist[i].setviewpoint(viewPoint);
			for (int i=0; i<m; i++)
    			elist[i].edge1(vlist[newdot1[i].a], vlist[newdot1[i].b]);
		} 
		void setviewPoint(double ro, double teta, double fi)
		{
			viewPoint.x = ro;
			viewPoint.y = teta;
			viewPoint.z = fi;
		}
};

int main()
{
	double ro=500, teta=0, fi=0;
	int d;
	int gddriver = DETECT, gmode;
	initgraph(&gddriver, &gmode, "");
	setfillstyle(LINE_FILL,BLACK) ; 
	Surface cube;
	cube.setviewPoint(ro, teta, fi);
	cube.load();	
	cube.draw();
	int button;
	while(true)   	{
		cleardevice();
		setcolor(4);
	
		if(button=='a') // ->
		teta += ((M_PI/10));
		if(button=='d') //<-
			teta -= ((M_PI/10));
		if(button=='w') //^
		fi += ((M_PI/10));
		if(button=='s') //_ 
		fi -= ((M_PI/10));
		if(button=='z')//-
		ro +=5;
		if(button=='c')//+
		ro -=5;
		if(button=='q'){
			exit(0);
		}
		cube.setviewPoint(ro,teta,fi); 
		cube.load();	
		cube.draw();
		button = getch();

	}
	getch();
	closegraph();
	return 0;
}

