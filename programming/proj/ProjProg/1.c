#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>


typedef struct
{
  gint x, y;
  gint flag_move;// Esta a "1" quando o rato esta carregado na lente 1 e a 2 na lente 2 e a "0" quando larga.
  gdouble     ratoPos[2];// Posicao do rato
  gdouble     press[2];// Posicao em que foi carregado o botao do rato
  gchar str1[128];
  gdouble centroe1[2];//coordenadas centro elipse 1
  gdouble centroe2[2];//coordenadas centro elipse 2
  gdouble deltax;//inicializado com um nr negativo pq no decorrer do programa vai ter sempre valores positivos. permite dar valores iniciais às variaveis.
  gdouble deltarato;
  gdouble f1;
  gdouble f2;
  gdouble xobj;
  gdouble xi1;
  gdouble dimobj;
  gdouble dimi1;
  gdouble dl2i1;
  gdouble dl1i1;
  gdouble magl1;
  gdouble magl2;
  gdouble dl2i2;
  gdouble dl1i2;
  gdouble xi2;
  gdouble dimi2;
  gdouble magt;
  gdouble magmax;
  GtkAdjustment *adj[4];
  GtkWidget *hscale[4];
  GtkWidget *window;
  gdouble draw;
}global;
 


//area desenho
gboolean
on_expose_event (GtkWidget      *widget,
		 GdkEventExpose *event,
		 gpointer data         )
{
  global *glob;
  cairo_t       *cr;
  double a,b;
  static const double dashed1[] = {3.0};


  glob=(global *) data;

  gtk_window_get_size (GTK_WINDOW(glob->window), &glob->x, &glob->y);



  if(glob->deltax<0)
    {

      glob->centroe1[0]=(glob->x)*0.125; 
      glob->centroe1[1]=(glob->y)*0.35;
      glob->centroe2[0]=(glob->x)*0.29;
      glob->centroe2[1]=(glob->y)*0.35;
      glob->xi1=glob->x*0.05;
      glob->xi2=glob->x*0.05;
    
    }
  glob->deltax=fabs(glob->centroe1[0]-glob->centroe2[0]);
  glob->f1=gtk_adjustment_get_value (glob->adj[0]);
  glob->f2=gtk_adjustment_get_value (glob->adj[1]);
  glob->xobj=glob->x*0.05+gtk_adjustment_get_value(glob->adj[2]);
  glob->dimobj=gtk_adjustment_get_value(glob->adj[3]);
  glob->magt=glob->magl1*glob->magl2;
 
  //restriçoes nas dfocais
  gtk_adjustment_set_upper (glob->adj[0],(gdouble)1+fabs(glob->centroe1[0]-glob->xobj));
  gtk_adjustment_set_upper (glob->adj[1],(gdouble)1+glob->x*0.6-glob->centroe2[0]);
 
  //restriçao na posiçao e dimensao objeto
  gtk_adjustment_set_upper (glob->adj[2],(gdouble)(1+glob->centroe1[0]-glob->f1-glob->x*0.05));
  gtk_adjustment_set_upper (glob->adj[3],(gdouble)1+glob->x*0.06);//altura das lentes
  cr = gdk_cairo_create (glob->window->window);


  // SEPARADORES
  // HORIZONTAL
  cairo_set_source_rgb (cr, 1, 1, 1);//cor
  cairo_set_line_width(cr, 2);
  cairo_move_to(cr, 0, 500);
  cairo_line_to(cr, 1300, 500 );
  cairo_stroke(cr);
 

  //vertical 1
  cairo_move_to(cr,270, 500);
  cairo_line_to(cr,270, 600);
  cairo_stroke(cr);


  //vertical 2
  cairo_move_to(cr,810, 500);
  cairo_line_to(cr,810, 600);
  cairo_stroke(cr);

  //vertical 3
  cairo_move_to(cr,960, 500);
  cairo_line_to(cr,960, 600);
  cairo_stroke(cr);

  //vertical 4
  cairo_move_to(cr,1300, 500);
  cairo_line_to(cr,1300, 600);
  cairo_stroke(cr);

  //vertical 5
  cairo_move_to(cr,1090, 0);
  cairo_line_to(cr,1090, 500);
  cairo_stroke(cr);



  
  //titulos
  cairo_set_source_rgb(cr, 0, 1, 0);
  cairo_select_font_face(cr, "Ubuntu Light", 
			 CAIRO_FONT_SLANT_NORMAL, 
			 CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 15);
  cairo_move_to(cr, 80, 520);
  sprintf (glob->str1, "Posições");
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr);

  //dimensoes
  cairo_move_to(cr, 830, 520);
  sprintf (glob->str1, "Dimensões");
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr);

  //distancias

  cairo_move_to(cr, 450, 520);
  sprintf (glob->str1, "Distâncias");
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr);

  //ampliações
  cairo_move_to(cr, 990, 520);
  sprintf (glob->str1, "Ampliação");
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr);


  //coords rato ref
  cairo_set_font_size(cr, 12);
  cairo_move_to(cr, 50, 540);
  sprintf (glob->str1, "Rato no Referencial: %4d %4d",(int) (glob->ratoPos[0]-glob->x*0.05), (int)(glob->y*0.35-glob->ratoPos[1]));
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr);

  //x lente 1
  cairo_move_to(cr, 20, 560);
  sprintf (glob->str1, "X Objetiva: %4.1lf",glob->centroe1[0]-glob->x*0.05);
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr);



  //x lente 2
  cairo_move_to(cr, 20, 580);
  sprintf (glob->str1, "X Ocular: %4.1lf",glob->centroe2[0]-glob->x*0.05);
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //x i 1
  cairo_move_to(cr, 140, 560); 
  sprintf (glob->str1, "X 1ª Imagem: %4.1lf",glob->xi1-glob->x*0.05);
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //x i 2

  cairo_move_to(cr, 140, 580); 
  sprintf (glob->str1, "X 2ª Imagem: %4.1lf",glob->xi2-glob->x*0.05);
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //d lentes
  cairo_move_to(cr, 450, 540);
  sprintf (glob->str1, "Das lentes: %4.1lf",glob->deltax);
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //d obj lente1

  cairo_move_to(cr, 280,560);
  sprintf (glob->str1, "Objeto à Objetiva: %4.1lf",fabs(glob->centroe1[0]-glob->xobj));
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //d obj lente2
  cairo_move_to(cr, 280,580);
  sprintf (glob->str1, "Objeto à Ocular: %4.1lf",fabs(glob->centroe2[0]-glob->xobj));
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 


  //d ima1 lente1
  cairo_move_to(cr, 440, 560);
  sprintf (glob->str1, "1ª Imagem à Objetiva: %4.1lf",fabs(glob->dl1i1));
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //d ima1 lente2
  cairo_move_to(cr, 440, 580);
  sprintf (glob->str1, "1ª Imagem à Ocular: %4.1lf",fabs(glob->dl2i1));
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //d ima2 lente1
  cairo_move_to(cr, 620, 560);
  sprintf (glob->str1, "2ª Imagem à Objetiva: %4.1lf",fabs(glob->dl1i2));
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //d ima2 lente2
  cairo_move_to(cr, 620, 580);
  sprintf (glob->str1, "2ª Imagem à Ocular: %4.1lf",fabs(glob->dl2i2));
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //dimensão imagem1
  cairo_move_to(cr, 820,560);
  sprintf (glob->str1, "1ª Imagem: %4.1lf",fabs(glob->dimi1));
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //dimensão imagem2
  cairo_move_to(cr, 820,580);
  sprintf (glob->str1, "Imagem Final: %4.1lf",fabs(glob->dimi2));
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //Ampliação atual
  cairo_move_to(cr, 980,560);
  sprintf (glob->str1, "Atual: %4.2lf",glob->magt);
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  //Ampliação máxima
  cairo_move_to(cr, 980,580);
  sprintf (glob->str1, "Máxima Registada: %4.2lf",glob->magmax);
  cairo_show_text  (cr, glob->str1);
  cairo_stroke(cr); 

  // Referencial
  //horizontal
  cairo_set_source_rgb (cr, 1, 1, 1);//cor
  cairo_set_line_width(cr, 2);
  cairo_move_to(cr, 0, glob->y*0.35);
  cairo_line_to(cr, glob->x*0.6, glob->y*0.35 );
  cairo_stroke(cr);
  cairo_select_font_face(cr, "Courier 10 Pitch", 
			 CAIRO_FONT_SLANT_NORMAL, 
			 CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 15);
  cairo_move_to(cr, glob->x*0.6-20,glob->y*0.35-20);
  cairo_show_text(cr, "x  mm");

  //vertical
  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_set_line_width(cr, 2);
  cairo_move_to(cr, glob->x*0.05, glob->y*0.8);
  cairo_line_to(cr, glob->x*0.05, glob->y*0.1);
  cairo_stroke(cr);
  cairo_select_font_face(cr, "Courier 10 Pitch", 
			 CAIRO_FONT_SLANT_NORMAL, 
			 CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 15);
  cairo_move_to(cr, glob->x*0.05-50,glob->y*0.1+20);
  cairo_show_text(cr, "y  mm");

  //elipse 1
  cairo_set_source_rgb (cr, 0, 0.75, 1);
  cairo_translate(cr,glob->centroe1[0],glob->centroe1[1]); //coordenadas centro elipse
  cairo_scale(cr, 0.15,2);// no tamanho padrao da janela a razao x:y é 0.15:2 "diametro"x elipse = 10.8; "diametro"y elipse = 72
  cairo_arc(cr, 0, 0, glob->x*0.03, 0, 2*M_PI);
  cairo_fill(cr);
  cairo_stroke(cr);


  //elipse 2
  cairo_identity_matrix(cr);
  cairo_set_source_rgb (cr, 0.44, 0.62, 0.94); 
  cairo_translate(cr,glob->centroe2[0],glob->centroe2[1]); //coordenadas centro elipse
  cairo_scale(cr, 0.15,2);//"diametro"x elipse = 10.8; "diametro"y elipse = 72
  cairo_arc(cr, 0, 0, glob->x*0.03, 0, 2*M_PI); //raio padrao = 36
  cairo_fill(cr); 
  cairo_stroke(cr); 

  //f1
  cairo_identity_matrix(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_translate(cr,glob->centroe1[0]+glob->f1,glob->y*0.35);

  cairo_arc (cr,0, 0, 3, 0, 2*M_PI);
     

  cairo_select_font_face(cr, "Courier 10 Pitch", 
			 CAIRO_FONT_SLANT_NORMAL, 
			 CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 15);
  cairo_move_to(cr, 0,-20);
  cairo_show_text(cr, "f1");
  
  cairo_fill(cr);
  cairo_stroke(cr);

  //f'1
  cairo_identity_matrix(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_translate(cr,glob->centroe1[0]-glob->f1,glob->y*0.35);

  cairo_arc (cr,0, 0, 3, 0, 2*M_PI);
     

  cairo_select_font_face(cr, "Courier 10 Pitch", 
			 CAIRO_FONT_SLANT_NORMAL, 
			 CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 15);
  cairo_move_to(cr, 0,-20);
  cairo_show_text(cr, "f'1");
  
  cairo_fill(cr);
  cairo_stroke(cr);
  //f2
  cairo_identity_matrix(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_translate(cr,glob->centroe2[0]+glob->f2,glob->y*0.35);

  cairo_arc (cr,0, 0, 3, 0, 2*M_PI);
     

  cairo_select_font_face(cr, "Courier 10 Pitch", 
			 CAIRO_FONT_SLANT_NORMAL, 
			 CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 15);
  cairo_move_to(cr, 0,20);
  cairo_show_text(cr, "f2");
  
  cairo_fill(cr);
  cairo_stroke(cr);

  //f'2
  cairo_identity_matrix(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_translate(cr,glob->centroe2[0]-glob->f2,glob->y*0.35);

  cairo_arc (cr,0, 0, 3, 0, 2*M_PI);
     

  cairo_select_font_face(cr, "Courier 10 Pitch", 
			 CAIRO_FONT_SLANT_NORMAL, 
			 CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 15);
  cairo_move_to(cr, 0,20);
  cairo_show_text(cr, "f'2");
  
  cairo_fill(cr);
  

  //objeto
  cairo_identity_matrix(cr);
  cairo_set_source_rgb (cr, 1, 0, 0);
  cairo_set_line_width(cr, 4);
  cairo_move_to(cr, glob->xobj, glob->y*0.35);
  
  cairo_line_to(cr, glob->xobj, glob->y*0.35-glob->dimobj);
  cairo_stroke(cr);
  
  cairo_fill(cr);
  cairo_stroke(cr);
  
  if(glob->draw==1)
    {
      //luz pa criar imagem1
      //raio qe vai pro foco
      if(glob->xobj != glob->centroe1[0])
	{
	  cairo_set_source_rgb (cr, 1, 1, 0);
	  cairo_set_line_width(cr, 2);
	  cairo_move_to(cr, glob->xobj,glob->y*0.35-glob->dimobj);
	  cairo_line_to(cr, glob->centroe1[0],glob->y*0.35-glob->dimobj );
	  cairo_stroke(cr);

	  cairo_set_source_rgb (cr, 1, 1, 0);
	  cairo_set_line_width(cr, 2);
	  cairo_move_to(cr, glob->centroe1[0],glob->y*0.35-glob->dimobj );

	  b=((glob->dimobj)/(glob->f1));

	  cairo_line_to(cr, glob->centroe1[0]+glob->f1,glob->y*0.35);
	  cairo_stroke(cr);

	  cairo_move_to(cr,  glob->centroe1[0]+glob->f1,glob->y*0.35);
	  if( glob->y*0.35+b*(glob->deltax-glob->f1)<=glob->y*0.35+glob->x*0.06)
	    {
	      cairo_line_to(cr, glob->centroe2[0],glob->y*0.35+b*(glob->deltax-glob->f1));
	      cairo_stroke(cr);
	    }
	  else
	    {
	      cairo_line_to(cr, glob->x*0.6,glob->y*0.35+b*(glob->x*0.6-glob->centroe1[0]-glob->f1));
	      cairo_stroke(cr);
	    }
    
	  //raio que passa no centro da lente
	  cairo_move_to(cr, glob->xobj,glob->y*0.35-glob->dimobj);
	  cairo_line_to(cr, glob->centroe1[0],glob->y*0.35);
	  cairo_stroke(cr);

	  cairo_set_source_rgb (cr, 1, 1, 0);
	  cairo_set_line_width(cr, 2);
	  cairo_move_to(cr, glob->centroe1[0],glob->y*0.35);

     
   
	  a=((glob->dimobj)/(glob->centroe1[0]-glob->xobj));
    
	  
	  if( glob->y*0.35+a*(glob->deltax)<=glob->y*0.35+glob->x*0.06)// padrao: 300 (ref)+72 ("diametro" em y da elipse)
	    {
	      cairo_line_to(cr, glob->centroe2[0],glob->y*0.35+a*(glob->deltax));
	      cairo_stroke(cr);

	    }
	  else
	    {
	      cairo_line_to(cr, glob->x*0.6,glob->y*0.35+a*(glob->x*0.6-glob->centroe1[0]));
	      cairo_stroke(cr);

	    }
	
     
	}

      //imagem1
      cairo_identity_matrix(cr);
      cairo_set_source_rgb (cr,0 , 1, 0);
      cairo_set_line_width(cr, 4);
      glob->dl1i1=((glob->f1*(glob->centroe1[0]-glob->xobj))/(-glob->f1+(glob->centroe1[0]-glob->xobj)));
      //dl1i1=f1*dobjal1/dobjal1-f1
      if((glob->centroe1[0]+glob->dl1i1)<(glob->centroe2[0]))
	{
	  glob->xi1=glob->centroe1[0]+glob->dl1i1;
 

	  cairo_move_to(cr,glob->xi1, glob->y*0.35);
  

	  glob->magl1=(-glob->dl1i1/(glob->centroe1[0]-glob->xobj));
	  glob->dimi1=(glob->dimobj*glob->magl1);

	  cairo_line_to(cr,glob->xi1, glob->y*0.35-glob->dimi1);
	  //ampliaçao=-dl1i1/dobjal1
	}
      else
	{

	  glob->xi1=glob->centroe2[0];
	  glob->dimi1=0;
    
 
	
	}

      cairo_stroke(cr);
      cairo_fill(cr);

      //luz real pa criar imagem2

      //raio que vai pro foco
      if(glob->centroe1[0]+glob->dl1i1 < glob->centroe2[0] && glob->centroe1[0]+glob->dl1i1>glob->x*0.05 )
	{
	
	  cairo_set_source_rgb (cr, 1, 0.55, 0);
	  cairo_set_line_width(cr, 2);
	  cairo_move_to(cr, glob->xi1,glob->y*0.35-glob->dimi1);
	  cairo_line_to(cr, glob->centroe2[0],glob->y*0.35-glob->dimi1 );
	  cairo_stroke(cr);

	 
	  cairo_move_to(cr, glob->centroe2[0],glob->y*0.35-glob->dimi1 );
	  cairo_line_to(cr, glob->centroe2[0]+glob->f2,glob->y*0.35);
	  cairo_stroke(cr);

	  cairo_move_to(cr, glob->centroe2[0]+glob->f2,glob->y*0.35);
	  cairo_line_to(cr, glob->x*0.6,glob->y*0.35-(-glob->dimi1/glob->f2)*(glob->x*0.6-(glob->centroe2[0]+glob->f2)));
	  cairo_stroke(cr);
      


	  //raio que passa no centro da lente
	  cairo_move_to(cr, glob->xi1,glob->y*0.35-glob->dimi1);
	  cairo_line_to(cr, glob->centroe2[0],glob->y*0.35 );
	  cairo_stroke(cr);

	  cairo_move_to(cr, glob->centroe2[0],glob->y*0.35);

	  glob->dl2i1=glob->centroe2[0]-(glob->xi1);
	  cairo_line_to(cr, glob->x*0.6,glob->y*0.35-(-glob->dimi1/glob->dl2i1)*(glob->x*0.6-(glob->centroe2[0])));
	  cairo_stroke(cr);

	}

      //luz virtual pa criar imagem 2

      //raio que passa no centro da lente
      if(glob->centroe1[0]+glob->dl1i1 < glob->centroe2[0] && glob->centroe1[0]+glob->dl1i1>glob->x*0.05 )
	{
	  cairo_set_dash(cr, dashed1, 1, 0);
	  cairo_set_source_rgb (cr, 1, 0.55, 0);
	  cairo_set_line_width(cr, 2);
	  cairo_move_to(cr, glob->xi1,glob->y*0.35-glob->dimi1);
	  cairo_line_to(cr, 0,glob->y*0.35+(-glob->dimi1/glob->dl2i1)*(glob->centroe2[0]));
	  cairo_stroke(cr);

	  //raio que passa no foco
	 
	  cairo_move_to(cr, glob->centroe2[0],glob->y*0.35-glob->dimi1);
	  cairo_line_to(cr, 0,glob->y*0.35+(-glob->dimi1/glob->f2)*(glob->centroe2[0]+glob->f2));
	  cairo_stroke(cr);
	}

      //imagem2
     
      cairo_set_dash(cr, dashed1, 0, 0);
      cairo_set_source_rgb (cr,0 , 0, 1);
      cairo_set_line_width(cr, 4);

      glob->dl2i2=fabs(((glob->f2*(glob->dl2i1))/(-glob->f2+(glob->dl2i1))));

      if(fabs(glob->dl2i1)<glob->f2)
	{
	  if(glob->magt>glob->magmax && glob->magt<5e3)
	    glob->magmax=glob->magt;

	  glob->xi2=glob->centroe2[0]-glob->dl2i2;
	  glob->dl1i2=fabs(glob->centroe1[0]-glob->xi2);
	  glob->magl2=(-glob->dl2i2/(glob->dl2i1));
	  glob->dimi2=(fabs(glob->dimi1)*glob->magl2);

	  if(glob->xi2>=0 && glob->xi2<=glob->x*0.6 && fabs(glob->dimi2)<glob->y*0.45)
	    {
 
	      cairo_move_to(cr,glob->xi2, glob->y*0.35);
	      cairo_line_to(cr,glob->xi2, glob->y*0.35-glob->dimi2);
	      cairo_stroke(cr);
	    }
	  else if(glob->xi2>=0 && glob->xi2<=glob->x*0.6 && fabs(glob->dimi2)>glob->y*0.45)
	    {
	      cairo_set_source_rgb (cr,0 , 1, 0);
	      cairo_select_font_face(cr, "Ubuntu Light", 
				     CAIRO_FONT_SLANT_NORMAL, 
				     CAIRO_FONT_WEIGHT_BOLD);
	      cairo_set_font_size(cr, 12);
	      cairo_move_to(cr, glob->x*0.1,50);
	      cairo_show_text(cr, "A dimensão da imagem final é superior ao eixo do referencial.");
	      cairo_move_to(cr, glob->x*0.1,70);
	      cairo_show_text(cr,"A sua dimensão e posição são as indicadas em baixo.");
	    }
	  else
	    {
	      cairo_set_source_rgb (cr,0 , 1, 0);
	      cairo_select_font_face(cr, "Ubuntu Light", 
				     CAIRO_FONT_SLANT_NORMAL, 
				     CAIRO_FONT_WEIGHT_BOLD);
	      cairo_set_font_size(cr, 12);
	      cairo_move_to(cr, glob->x*0.1,50);
	      cairo_show_text(cr, "A imagem final fica fora das margens. É virtual e invertida em relação ao objeto.");
	      cairo_move_to(cr, glob->x*0.1,70);
	      cairo_show_text(cr,"A sua dimensão e posição são as indicadas em baixo.");
	    }
	
	}
      else
	{
	  glob->xi2=glob->centroe2[0]+glob->dl2i2;

	  glob->dl1i2=glob->centroe1[0]-glob->xi2;
	  glob->magl2=(-glob->dl2i2/(glob->dl2i1));
	  glob->dimi2=(fabs(glob->dimi1)*glob->magl2);

	  cairo_set_source_rgb (cr,0 , 1, 0);
	  cairo_select_font_face(cr, "Ubuntu Light", 
				 CAIRO_FONT_SLANT_NORMAL, 
				 CAIRO_FONT_WEIGHT_BOLD);
	  cairo_set_font_size(cr, 12);
	  cairo_move_to(cr, glob->x*0.1,50);
	  cairo_show_text(cr, "A imagem final fica fora das margens. É real e invertida em relação à 1ª ,ou seja,");
	  cairo_move_to(cr, glob->x*0.1,70);
	  cairo_show_text(cr,"tem o sentido do objeto. A sua dimensão e posição são as indicadas em baixo.");

	}


    }
 
  cairo_destroy(cr);
  
  return FALSE;
}


gboolean
faz_motion_notify (GtkWidget  *widget ,
		   GdkEvent   *event  ,
                   gpointer    data)
{
  global *glob;  
  glob=(global *) data;


  if (event->type == GDK_MOTION_NOTIFY)
    {
      glob->ratoPos[0] = ((GdkEventMotion *)event)->x;
      glob->ratoPos[1] = ((GdkEventMotion *)event)->y;
      if(glob->flag_move==1)
	{
	  //restrições no movimento das lentes. Embora pareçam demasiadas ou repetitivas, tentando pô-las doutra forma ou retirando algumas não faz o desejado
	  if(glob->ratoPos[0]+glob->deltarato+glob->f1>glob->centroe2[0] && glob->xi1!=glob->centroe2[0]) //tamanho do ref em x - raio da elipse
	    glob->centroe1[0] = glob->centroe2[0]-glob->f1;
	  else if(glob->ratoPos[0]+glob->deltarato-glob->f1<glob->xobj && glob->xi1!=glob->centroe2[0])
	    glob->centroe1[0]=glob->xobj+glob->f1;
	  else if((glob->xi1==glob->centroe2[0] && glob->ratoPos[0] + glob->deltarato>glob->centroe1[0] && glob->centroe1[0]+glob->f1>glob->centroe2[0]-glob->f2) || (glob->xi1==glob->centroe2[0] && glob->ratoPos[0] + glob->deltarato<glob->centroe1[0] && glob->centroe1[0]+glob->f1<glob->centroe2[0]-glob->f2))
	    glob->centroe1[0]=glob->centroe2[0]-glob->deltax;

	  else
	    glob->centroe1[0] = glob->ratoPos[0] + glob->deltarato;

	}
      if(glob->flag_move==2)
	{
	  if(glob->draw==0 && (glob->ratoPos[0]+glob->deltarato-glob->f2)<glob->centroe1[0])
	    glob->centroe2[0] = glob->centroe1[0]+glob->f2;

	  else if((glob->ratoPos[0]+glob->deltarato+glob->f2)>glob->x*0.6)
	    glob->centroe2[0] = glob->x*0.6-glob->f2;
	  else if(glob->ratoPos[0]<glob->centroe1[0])
	    glob->centroe2[0]=glob->centroe1[0];
	  else if((glob->xi1==glob->centroe2[0] && glob->ratoPos[0] + glob->deltarato<glob->centroe2[0]))
	    glob->centroe2[0]=glob->centroe1[0]+glob->deltax;	   
	  else

	    glob->centroe2[0] = glob->ratoPos[0] + glob->deltarato;
	}
     
    
    }
  else if (event->type == GDK_BUTTON_PRESS)  
    { 
      glob->press[0] = ((GdkEventButton *)event)->x; 
      glob->press[1] = ((GdkEventButton *)event)->y; 
    
      //condições fazem com que só faça o comando se clicar nos limites da lente
      if (glob->press[0]>= (glob->centroe1[0]-glob->x*0.0045)  && glob->press[0]<= (glob->centroe1[0]+glob->x*0.0045) && glob->press[1]>= (glob->centroe1[1]-glob->x*0.06)  && glob->press[1]<= (glob->centroe1[1]+glob->x*0.06) )  
  	{  
	  glob->flag_move = 1; 
	  glob->deltarato= glob->centroe1[0]-glob->press[0]; 
  	}  

      if (glob->press[0]>= (glob->centroe2[0]-glob->x*0.0045)  && glob->press[0]<= (glob->centroe2[0]+glob->x*0.0045) && glob->press[1]>= (glob->centroe2[1]-glob->x*0.06)  && glob->press[1]<= (glob->centroe2[1]+glob->x*0.06) )  
  	{  
	  glob->flag_move = 2;  
	  glob->deltarato= glob->centroe2[0]-glob->press[0]; 
  	}  
    }  
  else if (event->type == GDK_BUTTON_RELEASE) 
    {
      glob->flag_move = 0; 
    }

  gtk_widget_queue_draw (glob->window);
  return FALSE;
}



gboolean
button_clicked(GtkWidget *w,
	       gpointer data)
{
  global *glob;

  glob=(global *) data;

  glob->centroe1[0]=(glob->x)*0.125; //xno ref inicial:90
  glob->centroe1[1]=(glob->y)*0.35;
  glob->centroe2[0]=(glob->x)*0.29;//xno ref inicial: 340
  glob->centroe2[1]=(glob->y)*0.35;

  gtk_adjustment_set_value (glob->adj[3],20);
  gtk_adjustment_set_value (glob->adj[2],20);
  gtk_adjustment_set_value (glob->adj[1],95);
  gtk_adjustment_set_value (glob->adj[0],50);
  glob->draw=0;
  glob->xi1=glob->x*0.05;
  glob->xi2=glob->x*0.05;
  glob->dl1i1=0;
  glob->dl1i2=0;
  glob->dl2i1=0;
  glob->dl2i2=0;
  glob->dimi1=0;
  glob->dimi2=0;
  glob->magmax=0;
  glob->magl1=0;
  glob->magl2=0;

  return TRUE;
}

gboolean
button1_clicked(GtkWidget *w,
                gpointer data)
{
  global *glob; 
  glob=(global *) data;

  glob->draw=1;


  return TRUE;
}


gboolean 
change_scale (GtkWidget  *w    , 
	      gpointer    data ) 
{ 
  global    *glob  ; 
  glob=(global *) data; 
 
  gtk_widget_queue_draw (glob->window); 

  return TRUE; 
} 

gboolean                        
faz_resize (GtkWidget  *w    , 
	    gpointer    data ) 
{ 
  gtk_widget_queue_draw (w); 

  return FALSE; 
} 




int
main (int argc, char **argv)
{
  GtkWidget *hbox, *hbox1,*vbox,*vbox1,*label[4],*button[3];
  char str1[30]="Distância Focal da Ocular",str[30]="Distância Focal da Objetiva",str2[30]="Posição objeto",str3[30]="Dimensão Objeto";
  global *glob;
  GdkPixbuf *image;
  GdkPixmap *background;
  GtkStyle *style;
  GdkColor color;
  glob=(global *) calloc(1,sizeof(global));
  glob->deltax=-1;
  glob->flag_move=0;
  gdk_color_parse("#00FF00", &color);

  gtk_init (&argc, &argv);

  //estrutura
  glob->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_default_size (GTK_WINDOW( glob->window), 1300, 600);
  gtk_window_set_modal(GTK_WINDOW(glob->window),TRUE);
  gtk_window_set_title (GTK_WINDOW ( glob->window), "Microscópio Ótico");
  gtk_widget_set_size_request (GTK_WIDGET( glob->window), 1300, 600);
  gtk_window_set_resizable (GTK_WINDOW(glob->window),FALSE);
  gtk_window_set_position (GTK_WINDOW ( glob->window), GTK_WIN_POS_CENTER);

  //fundo
  image = gdk_pixbuf_new_from_file ("t1.jpg", NULL); 
  gdk_pixbuf_render_pixmap_and_mask (image, &background, NULL, 0); 
  style = gtk_style_new (); 
  style->bg_pixmap[0] = background; 
  gtk_widget_set_style (GTK_WIDGET(glob->window), GTK_STYLE(style));
  //boxes
  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (glob->window), vbox);
 
  hbox = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_end (GTK_BOX (vbox), hbox, FALSE, FALSE, 50);
 
  hbox1 = gtk_hbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (vbox), hbox1);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_box_pack_end (GTK_BOX (hbox1), vbox1, FALSE, FALSE, 20);

  //botoes
  button[0] = gtk_button_new_with_label("Sair");
  gtk_widget_set_size_request(GTK_WIDGET(button[0]), 80, 35);
  gtk_box_pack_end (GTK_BOX (vbox1), button[0], FALSE, FALSE, 0);

  gtk_widget_modify_bg(GTK_WIDGET(button[0]), GTK_STATE_SELECTED, &color );
  gtk_widget_modify_bg(GTK_WIDGET(button[0]), GTK_STATE_NORMAL, &color );
  g_signal_connect(G_OBJECT(button[0]), "clicked", 
		   G_CALLBACK(gtk_main_quit), glob);
  
  button[1] = gtk_button_new_with_label("Reset");
  gtk_widget_set_size_request(GTK_WIDGET(button[1]), 80, 35);
  gtk_box_pack_end (GTK_BOX (vbox1), button[1], FALSE, FALSE, 0);
  

  gtk_widget_modify_bg(GTK_WIDGET(button[1]), GTK_STATE_SELECTED, &color );
  gtk_widget_modify_bg(button[1], GTK_STATE_NORMAL, &color );	  
  g_signal_connect(G_OBJECT(button[1]), "clicked", 
		   G_CALLBACK(button_clicked), glob);

  button[2] = gtk_button_new_with_label("Iniciar");
  gtk_widget_set_size_request(button[2], 80, 35);
  gtk_box_pack_end (GTK_BOX (vbox1), button[2], FALSE, FALSE, 0);


  gtk_widget_modify_bg( GTK_WIDGET(button[2]), GTK_STATE_SELECTED, &color );
  gtk_widget_modify_bg( GTK_WIDGET(button[2]), GTK_STATE_NORMAL, &color );
  g_signal_connect(G_OBJECT(button[2]), "clicked", 
		   G_CALLBACK(button1_clicked), glob);

	  
  //scales laterais
  //d focal 1
  label[0] = gtk_label_new (str);
  gtk_box_pack_start (GTK_BOX (vbox1), label[0], FALSE, TRUE, 10);
  glob->adj[0] = (GtkAdjustment *)gtk_adjustment_new (50.0, 0.1/* minimo */, 301.0/* maximo */, 0.1, 0.1, 0.1);
  glob->hscale[0] = gtk_hscale_new (GTK_ADJUSTMENT(glob->adj[0]));
  g_signal_connect (glob->adj[0], "value-changed", G_CALLBACK (change_scale), glob);

  gtk_widget_modify_fg(GTK_WIDGET(label[0]), GTK_STATE_NORMAL, &color);
  
  gtk_widget_modify_bg (GTK_WIDGET(glob->hscale[0]), GTK_STATE_NORMAL, &color);
  gtk_widget_modify_bg (GTK_WIDGET(glob->hscale[0]), GTK_STATE_SELECTED, &color);
  gtk_widget_modify_fg (GTK_WIDGET(glob->hscale[0]), GTK_STATE_NORMAL, &color);
  gtk_box_pack_start (GTK_BOX (vbox1),  glob->hscale[0], FALSE, TRUE, 0);

 
  //d focal 2
  label[1] = gtk_label_new (str1);
  gtk_box_pack_start (GTK_BOX (vbox1), label[1], FALSE, FALSE, 15);
  glob->adj[1] = (GtkAdjustment *)gtk_adjustment_new (95.0, 0.1, 301.0, 0.1, 0.1, 1.0);
  glob->hscale[1] = gtk_hscale_new (GTK_ADJUSTMENT ( glob->adj[1]));
  gtk_box_pack_start (GTK_BOX (vbox1),  glob->hscale[1], FALSE, TRUE, 0);
  g_signal_connect (glob->adj[1], "value-changed", G_CALLBACK (change_scale), glob);

  gtk_widget_modify_fg(GTK_WIDGET(label[1]), GTK_STATE_NORMAL, &color);

  
  gtk_widget_modify_bg (GTK_WIDGET(glob->hscale[1]), GTK_STATE_NORMAL, &color);
  gtk_widget_modify_bg (GTK_WIDGET(glob->hscale[1]), GTK_STATE_SELECTED, &color);
  gtk_widget_modify_fg (GTK_WIDGET(glob->hscale[1]), GTK_STATE_NORMAL, &color);

  //posição objeto
  label[2] = gtk_label_new (str2);
  gtk_box_pack_start (GTK_BOX (vbox1), label[2], FALSE, TRUE, 15);
  glob->adj[2] = (GtkAdjustment *)gtk_adjustment_new (20.0, 0, 719.0, 0.1, 0.1, 0.1);
  glob->hscale[2] = gtk_hscale_new (GTK_ADJUSTMENT ( glob->adj[2]));
 gtk_box_pack_start (GTK_BOX (vbox1),  glob->hscale[2], FALSE, FALSE, 0);
  g_signal_connect (glob->adj[2], "value-changed", G_CALLBACK (change_scale), glob);
 
 
  gtk_widget_modify_fg (GTK_WIDGET(label[2]), GTK_STATE_NORMAL, &color);
 
  gtk_widget_modify_bg (GTK_WIDGET(glob->hscale[2]), GTK_STATE_NORMAL, &color);
  gtk_widget_modify_bg (GTK_WIDGET(glob->hscale[2]), GTK_STATE_SELECTED, &color);
  gtk_widget_modify_fg (GTK_WIDGET(glob->hscale[2]), GTK_STATE_NORMAL, &color);

  //dimensão objeto
  label[3] = gtk_label_new (str3);
  gtk_box_pack_start (GTK_BOX (vbox1), label[3], FALSE, TRUE, 15);

  glob->adj[3] = (GtkAdjustment *)gtk_adjustment_new (20.0, 0,100, 0.1, 0.1, 0.1);
  glob->hscale[3] = gtk_hscale_new (GTK_ADJUSTMENT ( glob->adj[3]));
 gtk_box_pack_start (GTK_BOX (vbox1),  glob->hscale[3], FALSE, TRUE, 0);
  g_signal_connect (glob->adj[3], "value-changed", G_CALLBACK (change_scale), glob);
 
  gtk_widget_modify_fg(GTK_WIDGET(label[3]), GTK_STATE_NORMAL, &color);
  
  gtk_widget_modify_bg (GTK_WIDGET(glob->hscale[3]), GTK_STATE_NORMAL, &color);
  gtk_widget_modify_bg (GTK_WIDGET(glob->hscale[3]), GTK_STATE_SELECTED, &color);
  gtk_widget_modify_fg (GTK_WIDGET(glob->hscale[3]), GTK_STATE_NORMAL, &color);


  //signals e callbacks
  gtk_widget_set_events ( glob->window, GDK_POINTER_MOTION_MASK | GDK_BUTTON_PRESS_MASK |  GDK_BUTTON_RELEASE_MASK); 

  g_signal_connect ( glob->window, "motion-notify-event", G_CALLBACK (faz_motion_notify), glob); 
  g_signal_connect ( glob->window, "button_press_event", G_CALLBACK (faz_motion_notify), glob); 
  g_signal_connect ( glob->window, "button_release_event", G_CALLBACK (faz_motion_notify), glob);
  g_signal_connect (glob->window, "size-allocate", G_CALLBACK(faz_resize), glob);
  g_signal_connect( glob->window, "expose-event", G_CALLBACK(on_expose_event), glob);
  g_signal_connect ( glob->window, "destroy", G_CALLBACK(gtk_main_quit),glob);

  gtk_widget_set_app_paintable (glob->window, TRUE);
  gtk_widget_show_all (glob->window);
  gtk_main ();

  return 0;
}
