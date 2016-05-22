#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

class nodoSig{ // Clase NodoSig para elbergar informacion de los siguiendos
public:
		string sig1; // Valor siguiendo1
		string sig2;//valor sguiendo2
		nodoSig *next; // Próximo valor de la lista.
		nodoSig(string s1,string s2,nodoSig* n){ // Constructor de la clase nodo 
			sig1=s1;
			sig2=s2;
			next=n;
		}	
};

class listaSig{//clase lista para la informacion de los siguiendos 
	public:
		nodoSig *first; // Primer nodo de la lista
		listaSig(){
			first=NULL; // Inicializo la lista
		}		
		//prototipos de las funciones y acciones miembros de la clase listaSig
		bool VaciaSig();
		void InsertarSiguiendos(string a, string b);
		void InsertarSeguidores(string a, string b);
		void VerSeguidores(string user);
		void VerSiguiendos(string user);
		void DejarDeSeguir(string user);
		bool ComprobarSiSeguir(string user,string user2);
		void BuscarTweetSig(string nom_usua,string Arr2[],int cont,int& k);
		void GuardarInfoSiguiendos();
	};
	
class nodoTweets{ //clase nodoTweets que albergara informacion de los tweets
	public:
string _twitero;//valor del usuario que crea el tweet
string _tweet;//tweet que crea el usuario
nodoTweets *proxTweet;//apuntador al proximo tweet
nodoTweets(string t1,string t2, nodoTweets* _t){ //contructor de la clase nodoTweets
_twitero=t1;
_tweet=t2;
proxTweet=_t;
}
};	

class listaTweet{//clase lista para la informacion de los tweets
	public:
	nodoTweets *tweetPri;//apuntado primero del tweet
	listaTweet()
	{
		tweetPri=NULL; //se inicializa la lista
	}
	//prototipos de las acciones listasTweets
	bool VacioTweet();
	void InsertarTweet(string _t,string _t2);
	void EliminarTweet(string user,int cont);
	void VerMuro(string nom_usua,string tweetsig[],int k);
	void GuardarTweets();
};

class nodoUsers{ //clase nodo para albergar la informacion personal de los usuarios 
public:
string _nombre;
string _email;
string _nom_user;
string _pass;
nodoUsers *siguiente; //apuntador a siguiente
nodoUsers(string n,string m,string u,string p,nodoUsers* l){//constructor de la clase nodo
_nombre=n;
_email=m;
_nom_user=u;
_pass=p;
siguiente=l;	
}
};

class listaUsers{//clase lista para la informacion de la lista de usuarios 
public:
       nodoUsers *pri;
       listaUsers(){
		   pri=NULL;
	   }//prototipos de las acciones y funciones de la clase
	   bool VaciaUsers();
	   void InsertarUsers(string name,string mail,string name_user,string pass);
	   bool ValidarRegistro(string email, string nom_usua);
	   bool ValidarUsuario(string& usua, string pass);
	   void BuscarSeguir(string user,string following[],string& op);
	   void GuardarInfoUsuarios();	
};	
	
bool listaSig::VaciaSig(){return !first;} // Funcion de la lista que comprueba si esta  vacia 
void listaSig::InsertarSiguiendos(string a, string b){ // Acción de inserción para los siguiendos
//inserta ordenado de forma ascendente
if(VaciaSig()){	//verifico si esta vacia
first=new nodoSig(a,b,NULL); 
}
else{ //Si no esta vacia entonces...
nodoSig *aux=first;
if(aux->sig1 > a){ //si exite uno nodo , pero ese es mayor al que se quiere insertar , entonces se inserta el nuevo de primero
first=new nodoSig(a,b,aux);
}
else{
while(aux->next && aux->next->sig1 < a)//voy recorriendo la lista hasta encontrar uno mayor a el
{
aux=aux->next; 
}
aux->next=new nodoSig(a,b,aux->next);
}}}
	
void listaSig::InsertarSeguidores(string a, string b)
{//analogo a la accion anterior , solo que aqui ordenamos con respecto a b, osea al usuario que es seguido
if(VaciaSig())
{				 
first=new nodoSig(a,b,NULL); 			 
}
else{ //Si no esta vacia entonces...
nodoSig *aux=first;
if(aux->sig2 > b){ 
first=new nodoSig(a,b,aux);					
}
else{
while(aux->next && aux->next->sig2 < b){
aux=aux->next; 
}
aux->next=new nodoSig(a,b,aux->next);			   	    
}}}

void listaSig::VerSeguidores(string user)
{//accion que muestra los seguidores de un usuario x
nodoSig *S;
S=first;
cout<<endl;
cout <<"Los seguidores de "<<user<<" Son: "<<endl;
while(S->next!=NULL){//recorro la lista hasta que sea nulo
if(S->sig2 == user){//verifico si el usuario es igual al sig2 , si es asi muestro el sig1, ya que la relacion es A sigue a B
cout<<S->sig1<<endl;
}
S=S->next;//Pasamos al siguiente 
}
if(S->sig2 == user){//verificamos finalmente si el ultimo tambien es su seguidor
cout<<S->sig1<<endl;//y lo mostramos
}}
		
void listaSig::VerSiguiendos(string user)
{//analogo a la accion anterior , solo que aqui se van a mostrar los sig2 ya que verificaremos si el usuario es igual al sig1 
nodoSig *S;
S=first;
cout<<endl;
cout <<"Los siguiendos de "<<user<<" Son: "<<endl;		
while(S->next!=NULL)
{
if(S->sig1 == user)
{
cout<<S->sig2<<endl;
}
S=S->next;
}
if(S->sig1 == user)
{
cout<<S->sig2<<endl;
}}
		
void listaSig::DejarDeSeguir(string user){//accion que hace que un usuario deje de seguir a otro	
		    nodoSig *C;	
			C=first;
			int k=0;
			while(C!=NULL && C->next!=NULL){//recorro la lista para saber a cuantos el sigue
		    if(C->sig1 == user){//si el sigue a alguien,aumento el k , esto es basicamente para buscar a cuantos el sigue y poder hacer validaciones futuras
		    k++;
		    }
		    C=C->next;
			}
			if(C->sig1 == user){//veo si sigue al ultimo
				k++;
			}
			if(k>0){//Si k>0 es que el usuario si sigue a alguien, en caso contrario pues el no sigue a nadie
			string Elem[k];//declaro un arreglo de string para guardar los usuarios que el sigue
			C=first;
			int t=0;
			while(C!=NULL && C->next!=NULL){//recorro de nuevo la lista para saber cuales usuario se puede dejar de seguir
		    if(C->sig1 == user){//verifico si es el valor 
			Elem[t]=C->sig2; //guardo en el arreglo el valor del usuario que el sigue
		    t++;
		    }
		    C=C->next;
			}
			if(C->sig1 == user){//verifico si es el valor 
			Elem[t]=C->sig2; //guardo en el arreglo el valor del usuario que el sigue
		    t++;
		    }
			int option; //le indico al usuario que usuario desea no seguir
			DejarSeg:
			cout<<"Indique el usuario al cual desea dejar de seguir "<<endl;
			for(int j=0;j<t;j++) //muestro todos los valores que busque anteriormente
			{
				 cout <<j+1<<")"<<"  "<<Elem[j]<<endl;
			}
			cout <<t+1<<")"<<"  "<<"Salir"<<endl; //la opcion t+1 seria la de salir
			cin >> option;//leo la opcion del usuario
			if(option == t+1){goto End;} //si la opcion fue salir voy a fin entonces
			if(option < 0 || option > t+1){ cout<<"Opcion invalida, Intente de nuevo "<<endl; goto DejarSeg; }
			option--; //resto 1 a la opcion por el asunto de los indices		
			string st=Elem[option];//guardo el valor string en una variable para no estar accediendo a memoria a cada rato  hacerlo mas eficiente .   
		        nodoSig *E=first; // Si no esta vacia, existe un primer nodo
				if(E->next==NULL &&  (E->sig1==user && E->sig2==st)){ // Si es un unico nodo en toda la lista.
					first=NULL;//entonces elimino
					delete E;
				}
				else if(E->next!=NULL && (E->sig1==user && E->sig2==st)){ //Si existe otro nodo en la lista, pero es el primero quien debe ser eliminado. me paso al siguiente nodo y elimino el que se indico
					first=E->next;
					delete E;
				}
				else{
					nodoSig *act=E->next; //nodo actual para ir verificando un paso mas adelante
					while(act!=NULL && act->next!=NULL && act->sig2!=st){ //voy recorriendo la lista hasta no encontrar el valor,hago esto es para situarme en el sitio donde esta el valor
						act=act->next; //muevo los apuntadores
						E=E->next; 
					}
					if( act!=NULL && act->sig1==user && act->sig2==st){//verifico si es el usuario que se desea eliminar
						E->next=act->next; //muevo los apuntadores 
						delete act;//elimino 
						cout<<"Operacion Exitosa"<<endl;
					}
				}    
		    }else{//si k fue 0 , es que el usuario no sigue a nadie
				cout<<"El usuario :"<<user<<" No sigue a ningun otro usuario "<<endl; 	
	        }
	        End:;//fin accion
		}
	
		bool listaSig::ComprobarSiSeguir(string user,string user2){//funcion que comprueba si un usuario x ya sigue a un usuario y
		nodoSig *T;
	    T=first;
	    while(T!=NULL && T->next!=NULL){//recorro mientras no sea null
		if(T->sig1==user && T->sig2 == user2){ //compruebo si ya ese usuario x ya sigue a un usuario y
					return true;//si es asi entonces retorno TRUE
		}
	    T=T->next;	//Pasamos al valor siguiente
		}
		if(T->sig1==user && T->sig2==user2){//verificamos el ultimo valor 
		return true;
	    }
		return false;//en caso contrario retornamos falso ya que el usuario x no sigue a un usuario y
		}
		
		void listaSig::BuscarTweetSig(string nom_usua,string Arr2[],int cont,int& k)
		{//accion que busca los siguiendo de un usuario para luego ver sus tweets
			nodoSig *A;
			A=first;
			int i=0;
			while(A->next!=NULL){//recorro la lista 
		    if(A->sig1==nom_usua){//verifico si en la lista esta el usuario a quien se le va a buscar siguiendo
			Arr2[i]=A->sig2;//si es asi, al arreglo se le asigna el valor proximo de la lista, osea el usuario a quien el sigue
			i++;
		    }
		    A=A->next;
			}
			 if(A->sig1==nom_usua){//Veo si de casualidad sera el ultimo a ver
			Arr2[i]=A->sig2;//si es asi lo guardo en el arreglo
			i++;
		    } 
			k=i;//le asigno a k el numero de siguiendos que se encontro
		}
		
		 void listaSig::GuardarInfoSiguiendos()
		  {//Accion que guarda la informacion de los siguiendos en el archivo
			  nodoSig *SAVE;
			  SAVE=first;
			  fstream F;
			  F.open("entrada.in",ios::out | ios::app);//se abre en modo lectura y escritura
			  F<<"siguiendos"<<endl;//se escribe asi para respetar el formato
			  while(SAVE->next!=NULL){ //se recorre la lista 
				F<<SAVE->sig1<<" "; //se guarda el usuario
				F<<SAVE->sig2<<endl;   //se guarda el siguiente
				SAVE=SAVE->next;   //se pasa al siguiente campo
			  }
			    F<<SAVE->sig1<<" ";  //se guarda el ultimo campo
				F<<SAVE->sig2<<endl; 	  
		  }
		
bool listaUsers::VaciaUsers(){return !pri;}//funcion que verifica si es vacia la lista
		
void listaUsers::InsertarUsers(string name,string mail,string name_user,string pass){ // Acción de inserción de la informacion personal del usuario
if(VaciaUsers())pri=new nodoUsers(name,mail,name_user,pass,NULL); //verifico si ya esta vacia y creo un primer nodo
else{ //sino..
nodoUsers *aux=pri; //se crea un nodo auxiliar, y el primero se pone a apuntar al nuevo que se creo 
pri=new nodoUsers(name,mail,name_user,pass,aux);	 
}}
		 
bool listaUsers::ValidarRegistro(string email, string nom_usua){//funcion que valida si ya un usuario se registro previamente,verificaremos principalmente el email y el nombre de usuario ya que estos son los unicos que no se pueden repetir los demas es irrelevante
		  nodoUsers *T;
		  T=pri;
		  while(T->siguiente != NULL){//recorro hasta que sea null
		  if(T->_email==email || T->_nom_user==nom_usua){//verficamos si se repite el email o el nombre de usuario
		  return false; //retornamos false indicando que ese usuario no se puede registrar ya que existe uno igual
			  }
			  T=T->siguiente;//pasamos al siguiente
		  }
		  if(T->_email==email || T->_nom_user==nom_usua){//finalmente verificamos el ultimo campo
				  return false;
			  }
			  return true;//en caso contrario si se puede registrar 
	      }
	  
	  bool listaUsers::ValidarUsuario(string& usua, string pass)
      {//funcion que busca el nombre de usuario y la contraseña 
		 nodoUsers *elem;//se crea un apuntador a nodo
		 elem = pri;//se le asigna el primer elemento
		 while(elem->siguiente != NULL){//voy recorriendo la lista para ver si los valores exinten en ella
		 if( (elem->_email==usua || elem->_nom_user==usua) && elem->_pass==pass){//si ambos valores existen, retorno verdadero 
				 usua=elem->_nom_user;
				 return true;
		 }
		 elem=elem->siguiente; //sino paso a los siguientes campos para seguir verificando hasta que la lista sea nula
		 }
		 if((elem->_email==usua || elem->_nom_user==usua) && elem->_pass==pass){//aqui verifico de nuevo ya que el while se sale y no verifica el ultimo 
		 usua=elem->_nom_user;
		 return true; //una vez lo encuentre se retorna verdadero
		 } 
		 return false; //si no se encontro, bueno se retorna falso
	 }
	 
	 void listaUsers::BuscarSeguir(string user,string following[],string& op){//funcion que muestra las posibles opciones a las que un usuario puede seguir, sin incluirlo a el. 
			nodoUsers *C;	
			C=pri;
			int k=0;
			while(C->siguiente!=NULL){//recorremos hasta que sea null
		    if(C->_nom_user != user){//verificamos si en la lista de los usuarios no esta el , para guardar el posible usuario a seguir
		    following[k]=C->_nom_user;//guardamos el usuario
		    k++;
		    }
		    C=C->siguiente;//pasamos al siguiente
			}
			if(C->_nom_user != user){//verificamos el ultimo a ver..
				following[k]=C->_nom_user;
				k++;
			}
			int opcion;
			do{//le mostramos las opciones enumeradas 
			cout<<"Indique al usuario al cual desea seguir "<<endl;
			for(int l=0;l<k;l++){
				cout <<l+1<<") "<<following[l]<<endl;
			}
			 cout <<k+1<<") "<<"Salir"<<endl;//le indicamos que con esa opcion puede salir
			 cin>>opcion;//leemos la opcion
			 if(opcion == k+1){ //si la opcion fue salir
				  op="";//asignamos vacio a la opcion
				  goto Fin; }//nos vamos a fin de una 
			 }while(opcion <= 0 || opcion >k+1);//se valida que ingrese una opcion correcta 
			 opcion--;//se le resta 1 por el asunto de los indices
			 op=following[opcion];//se guarda en la variable que fue pasada por ref.
			Fin:;
		}
		
	     void listaUsers::GuardarInfoUsuarios()
	     { //Accion que guarda la informacion personal de los usuarios tales como nombre,email,nombre de usuario,y contraseña
			  nodoUsers *SAVE;
			  SAVE=pri;
			  fstream f;
			  f.open("entrada.in",ios::out); //se abre el archivo en modo escritura
			  f<<"usuarios"<<endl;//se escribe asi para respentar el formato
			  while(SAVE->siguiente!=NULL){//se recorre la lista 
			  f<<SAVE->_nombre<<" "; //se escribe el campo nombre
			  f<<SAVE->_email<<" ";//se escribe el campo email
			  f<<SAVE->_nom_user<<" ";//se escribe el campo nomUsuario
			  f<<SAVE->_pass<<endl;//se escribe el campo contraseña
			   SAVE=SAVE->siguiente;//se pasa a los siguientes campos
			  }
			  f<<SAVE->_nombre<<" "; //se escribe el campo nombre
			  f<<SAVE->_email<<" ";//se escribe el campo email
			  f<<SAVE->_nom_user<<" ";//se escribe el campo nomUsuario
			  f<<SAVE->_pass<<endl;//se escribe el campo contraseña  			  
		  } 
	
    bool listaTweet::VacioTweet(){return !tweetPri;}//funcion que valida si la lista esta vacia

	void listaTweet::InsertarTweet(string _t,string _t2){ // Acción de inserción de tweets, inserta el ultimo de primero
    if(VacioTweet())tweetPri=new nodoTweets(_t,_t2,NULL); //verifico si ya esta vacia y creo un primer nodo
	else{ //sino..
	nodoTweets *aux=tweetPri; //se crea un nodo auxiliar, y el primero se pone a apuntar al nuevo que se creo 
	tweetPri=new nodoTweets(_t,_t2,aux);	 
	}}
	
	void listaTweet::EliminarTweet(string user,int cont)
		    {//Accion que elimina un tweet de un usuario dado
			nodoTweets *A;
			A=tweetPri;
			string Elem[cont];//creo un arreglo de los posibles tweets que el usuario valla a eliminar
			int k=0;
			while(A->proxTweet!=NULL){ //busco los tweet que pertenecen a ese usuario en particular
		    if(A->_twitero==user){ //si es el usuario
			Elem[k]=A->_tweet; //guardo el siguiente valor , osea el tweet
		    k++;
		    }
		    A=A->proxTweet;
			}
			 if(A->_twitero==user){ //verifico si el ultimo es tambien del usuario
			Elem[k]=A->_tweet; //guardo el siguiente valor , osea el tweet
		    k++;
		    }      
		    if(k>0){ //ahora bien si k>0 es que el usuario si tiene tweets,caso contrario el usuario no tiene tweets que eliminar
		    int opcion;  //le doy informacion al usuario 
	             do{
	             cout <<"Indique el tweet que desea eliminar :"<<endl; 	    
		         for(int l=0;l<k;l++){//muestro los posibles valores tweets que pueda eliminar
			     cout <<l+1<<") ";
			     cout<<Elem[l]<<endl;
		         }
				 cout <<k+1<<")"<<" "<<"Salir"<<endl;
			     cin >> opcion;//leo la opcion 
			     if(opcion==k+1){goto EndTweet;}//si la opcion fue k+1 osea salir, nos vamos a la etiqueta fin 
			     }while(opcion <= 0 || opcion > k+1); //valido para que la opcion este dentro del rango permisible y no nos de una cosa ilogica
			     opcion--;//se le resta 1 a la opcion por cuestiones de indice		     
			     string OP=Elem[opcion];//se lo asigno a una variable para no estar accediendo a cada rato a una posicion de un arreglo
			     nodoTweets *aux=tweetPri; // Si no esta vacia, existe un primer nodo
				 if(aux->proxTweet==NULL && aux->_tweet==OP){ // Si es un unico nodo en toda la lista... se borra pues
					tweetPri=NULL;
					delete aux;
				}
				else if(aux->proxTweet!=NULL && aux->_tweet==OP){ //Si existe otro nodo en la lista, pero es el primero quien debe ser eliminado. entonces ce elimina
					tweetPri=aux->proxTweet;
					delete aux;
				}
				else{ //si no fue ninguna de las opciones anteriores entonces hay que recorrer la lista para encontrar el valor a eliminar
					nodoTweets *act=aux->proxTweet; //creo un nodo actual
					while(act!=NULL && act->proxTweet!=NULL && act->_tweet!=OP){ // Voy recorriendo hasta que encuentre el nodo que quiero eliminar
						act=act->proxTweet;
						aux=aux->proxTweet;
					}
					if(act!=NULL && act->_tweet==OP){//una vez llegado al valor se procedera a eliminar 
						aux->proxTweet=act->proxTweet;
						delete act;
					}}
				cout<<endl;
				cout<<"Tweet eliminado con exito."<<endl; //mensaje de la operacion eliminar
				cout<<endl;  
			 }else{//en caso contrario de que el usuario no halla tenido tweets...
				 cout<<endl;
			     cout<<"El usuario "<<user<<" No tiene tweet que eliminar "<<endl;
			     cout<<endl;
			    }
			    EndTweet:;//etiqueta final
			 }
	       	
		void listaTweet::VerMuro(string nom_usua,string tweetsig[],int k)
		{//Accion que mostrara los tweet tanto de las persona a que sigue como los propios 
			nodoTweets *Z;
			Z=tweetPri;
			cout<<endl;
		    cout<<"Tweets"<<endl;
		    int iter=0;
		    //aqui se muestran los tweet del usuario que el sigue
		    //ya que en el arreglo tweetsig guarde anteriormente los usuarios a quien el sigue
		    //el arreglo tweesig se lleno en BuscarTweetSig()
		    for(int j=0;j<k+1;j++){//hago un for porque tengo que mostrar todos los tweets posibles del usuario	
			while(Z->proxTweet!=NULL){//recorro hasta que no sea null
		    if(Z->_twitero==tweetsig[j]){ //comparo si el usuario corresponde a su tweet
			cout<<iter+1<<")"<<Z->_tweet<<endl; //muestro finalmente su tweet
			iter++;
		    }
		    Z=Z->proxTweet;//paso al siguiente campo
			}
			 if(Z->_twitero==tweetsig[j]){//nuevamente verifico si el valor coincide con el ultimo
			cout<<iter+1<<")"<< Z->_tweet<<endl;
			iter++;
		    } 
		    Z=tweetPri;//una vez que ya mostre todos los tweet de ese usuario tengo que volver al primero para verificar con los de mas .
		    }
		    nodoTweets *T;
		    T=tweetPri;
		    while(T->proxTweet!=NULL){//nuevamente tengo que recoorrer la lista para encontrar los tweets propios del usuario
		    if(T->_twitero==nom_usua){//voy verificando si es un tweet propio
			cout<<iter+1<<")"<<T->_tweet<<endl;//muestro 
			iter++;
		    }
		    T=T->proxTweet;
			}
			 if(T->_twitero==nom_usua){//voy verificando si es un tweet propio
			cout<<iter+1<<")"<<T->_tweet<<endl;//muestro 
			iter++;
		    }}
	
	       void listaTweet::GuardarTweets()
		  {//accion que guarda los tweets en el archivo
			  nodoTweets *SAVE;
			  SAVE=tweetPri;
			  fstream F;//se crea una variable tipo archivo
			  F.open("entrada.in",ios::out | ios::app); //se abre de escritura y añanir
			  F<<"tweets"<<endl;//se escribe respentando el formato
			  while(SAVE->proxTweet!=NULL){ //se recorre las lista
				F<<SAVE->_twitero<<" ";
				F<<SAVE->_tweet<<endl; // se escribe el usuario
				SAVE=SAVE->proxTweet;  //se pasa al siguiente campo
			  }
			F<<SAVE->_twitero<<" ";
			F<<SAVE->_tweet<<endl; // se escribe el usuario
			F.close();
		  }  

int main(){
listaSig foll1,foll2; //foll1 se guardara los siguiendos ordenados con respecto a sig1 , y foll2 se guardara ordenado con respecto a sig2	
listaUsers USERS; //lista para informacion del usuario
listaTweet TWEET; //lista para guardar el usuario seguido va el tweet
int contUsers=0,contTweets=0,contSig=0,opcion,opcion2,k,tam,tamano;//contadores para saber mas o menos a priori cuantos elementos tengo, y para guardar las opciones y eso..
//variables para leer los campos 
string nombre,email,nom_usuario,password,primeraLinea,tweetaux;
string siguiendo1,siguiendo2;
string tweetsUsuario, tweets;
string lineaTweets;
string aux,aux2,usua_aux,t;
bool enc1,enc2,enc3;//variable para verificar si un usuario existe, entre otras cosas...
//verifico si el archivo se puede abrir
fstream file; //variable para abrir el archivo
file.open("entrada.in",ios::in);//se abre el archivo en modo lectura
if(!file.is_open()){//valido si no se ha cargado el archivo
	cout <<"Error, el archivo no pudo ser leido"<<endl;	
}else{//sino
	//se lee la primera linea
	file >> primeraLinea;
     //Segmento de usuarios 
	while(!file.eof()){//verifico si no es fin de archivo
	file >> nombre; //leo el nombre
	if(nombre == "siguiendos")//verifico si estamos en el final de usuarios
	{break;}
	file >> email;  //leo el email
	file >> nom_usuario; //leo en nombre de usuario
	file >> password;// leo el password
	//inserto todos los elementos en la lista
	USERS.InsertarUsers(nombre,email,nom_usuario,password);	
	contUsers++;
    }
         //segmento de siguiendos 
    while(!file.eof()){//verifico si no es fin de archivo
		file >> siguiendo1; //leo el primer usuario
		if(siguiendo1 == "tweets") //verifico si no estamos en  el final
		{break;}	
		file >> siguiendo2; //leo el siguiente usuario	
		foll1.InsertarSiguiendos(siguiendo1,siguiendo2);//se guarda los campos de siguiendos
		foll2.InsertarSeguidores(siguiendo1,siguiendo2); //se guarda los campos de seguidores
		contSig++;
	}
		    //segmento de tweets
	while(!file.eof()){//verifico si no es fin de archivo
		file >> nom_usuario; //leo el usuario
		getline(file,lineaTweets); //leo la linea completa del string del tweet 	
		if(file.eof())//verifico si ya estoy en el final del archivo
		{break;} //y asi no hacer una iteracion innecesaria
		tamano=lineaTweets.length();//esto es para sacar el tamaño del tweet
		tweetaux=lineaTweets.substr(1,tamano);//Y es para que no agarre la linea con todo y espacio sino solamente el tweet
		TWEET.InsertarTweet(nom_usuario,tweetaux);//inserto el usuario y su respectivo tweet
		contTweets++;
	}
	file.close();//cierro el archivo
	// menu principal
	MENU: //etiqueta de menu
	do{	
	cout <<"MENU"<<endl;
	cout <<"1) Registrar Usuario "<<endl;
	cout <<"2) Iniciar secion "<<endl;
	cout <<"3) Salir"<<endl;
	cin>>opcion;
    }while(opcion!=1 && opcion!=2 && opcion!=3); //valido que este en el rango de la opciones
    if(opcion==3){exit(0);}//opcion salir
	switch(opcion){//menu opcion
		case 1: 
	    do{
	    cout <<"Indique Nombre, Email, Nombre de usuario y clave."<<endl;
	    cin >> nombre >> email >> nom_usuario >> password;
	    enc2=USERS.ValidarRegistro(email,nom_usuario);//validamos que no sea un usuario repetido  
	    }while(enc2==false);
	  //una vez leido los datos para registrar los usuarios se guardan los mismo en la lista
      //inserto todos los elementos en la lista
	USERS.InsertarUsers(nombre,email,nom_usuario,password);
	contUsers++;
       cout <<endl;
	   cout <<"Usuario registrado con exito "<<endl;
	   cout <<endl;
	    goto MENU;
	    break;
		case 2:
        do{
		cout <<endl;		
		cout <<"Indique nombre de usuario y clave "<<endl;
		cin >> nom_usuario >> password;
		enc1 = USERS.ValidarUsuario(nom_usuario,password);//validamos si ese usuario esta registrado, puede loguearse con email o nombre de usuario, es indiferente
	    }while(enc1!=true); //una vez logueado se muestra el submenu
	     do{
		SubMenu:
		cout<<endl;	 
		cout<<"1)Ver seguidores"<<endl;
        cout<<"2)Ver siguiendos"<<endl;
        cout<<"3)Crear tweet"<<endl;
        cout<<"4)Eliminar tweet"<<endl;
        cout<<"5)Seguir"<<endl;
        cout<<"6)Dejar de seguir"<<endl;
        cout<<"7)Ver muro"<<endl; 
        cout<<"8)Guardar en archivo"<<endl;
        cout<<"9)Salir"<<endl;
        cin >> opcion2;
        if(opcion2 < 1 || opcion2 >9){cout<<"¡Opcion Invalida!"<<endl; goto SubMenu;} //si la opcion fue invalida volvemos al menu
           if(opcion2==1){   
			cout<<"Indique nombre de usuario "<<endl;
			cin >> usua_aux;//pedimos el nombre de usuario
			foll1.VerSeguidores(usua_aux);//finalmente los mostramos , si es que tiene
		    }
			if(opcion2==2){
			cout<<"Indique nombre de usuario "<<endl;
			cin >> usua_aux;
		    foll2.VerSiguiendos(usua_aux);//analogo a la opcion anterior
		    }
		    if(opcion2==3){//opcion de crear tweet
			tweet:
			cout <<"Indique el Tweet a crear :"<<endl;
            cin.ignore();
            getline(cin,t);
            tam = t.length();//esto es porque el usuario puede ingresar el tweet con espacios
            if(tam <= 140){ //validamos que sean solo 140 caracteres
		    TWEET.InsertarTweet(nom_usuario,t);	//si es asi entonces se crea el tweet
		    cout<<endl;
		    cout <<"Tweet creado con exito."<<endl;
		    cout<<endl;
		    contTweets++;
		    }else{ //sino le indicamos que se equivoco y le invitamos a que lo haga de nuevo
				cout<<endl;
				cout <<"Error, los tweets tienen que ser de 140 caracteres"<<endl;
				cout<<endl;
				goto tweet;
			}}
			if(opcion2==4){ //opcion que elimina un tweet de un usuario particular
	        TWEET.EliminarTweet(nom_usuario,contTweets);
		    }
	         if(opcion2==5){//opcion seguir
	        string Arr[contUsers];//creamos un array de string para guardar los usuarios que ya estan registrados
	        Seguir:
	        USERS.BuscarSeguir(nom_usuario,Arr,aux);//llenamos ese arreglo para mostrarle los que puede seguir sin incluirlo a el. 
	        if(aux!=""){ //esto fue si eligio seguir a alguien , ese valor esta en aux
	        enc3=foll1.ComprobarSiSeguir(nom_usuario,aux);//comprobamos si ya el sigue al usuario como tal 
	        if(enc3==true){//si es asi le decimos que ya el lo sigue y le invitamos a seguir a otro
			cout<<"Ya usted sigue al usuario "<<aux<<" "<<"Intente de nuevo "<<endl;
			cout<<endl;
			goto Seguir;
		 	}else{ //si no es asi entonces hacemos que lo siga   
	        foll1.InsertarSiguiendos(nom_usuario,aux);
		    foll2.InsertarSeguidores(nom_usuario,aux);
	        contSig++;
	        cout<<endl;
	        cout<<"Usuario seguido con exito "<<endl;
	        cout <<endl;
		    }}}
	        if(opcion2==6){ //opcion dejar de seguir 
	        foll2.DejarDeSeguir(nom_usuario); //accion que le indicara cual quiere no seguir, si no sigue a nadie , se le dira que el no sigue a nadie      
	        }
	        if(opcion2==7){ //opcion ver muro
	        string Arr2[contSig];//creo un arreglo para guardar los posibles siguiendos que existan
	        foll1.BuscarTweetSig(nom_usuario,Arr2,contSig,k);//lleno el arreglo con los usuarios que el sigue
	        TWEET.VerMuro(nom_usuario,Arr2,k);//luego muestro los tweets de los tweets de sus siguiendo y los de el 
	        }
			if(opcion2==8){ //opcion guardar archivo , se guardan de nuevo todas las lista modificadas en el archivo entrada.in
		    USERS.GuardarInfoUsuarios(); 
		    foll1.GuardarInfoSiguiendos();
		    TWEET.GuardarTweets();
		    cout<<"Documento guardado con exito "<<endl;
		    cout<<endl;
		    goto MENU;	//volvemos a loguearnos
     		} 
		    if(opcion2==9){//salimos
			exit(0);
		    }	
	      }while(opcion2 >=1 && opcion2 <=9);     		
		if(opcion==3){//opcion salir
			exit(0);
		}
	}
return 0;
}}//Fin de todo.
