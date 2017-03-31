/* 
|  FILE        :   ListTool2B.h
|
|  AUTHOR      :   Frode Haug, NTNU
|
|  IMPORT      :      None
|  EXPORT      :      None
|
|  DESCRIPTION :   
|          Toolkit for handling of lists (LIFO, FIFO and NUMERIC/TEXT SORTED).
|          For more details:  see "LISTTOOL.HTM" (in norwegian).
|
|
+---------------------------------------------------------------------------+
|                      C H A N G E     H I S T O R Y
+----------+-------------------------------------------+--------------------+
|   DATE   |  DESCRIPTION                              |  SIGN
+----------+-------------------------------------------+--------------------+
|  020594  |  Initial.                                 |  Frode Haug
|  270495  |  Virtual destructor in Element.           |  Frode Haug
|  170497  |  Extended if-test in remove(.....) (2x)   |  Frode Haug
|  040400  |  Some few small cosmetic corrections.     |  Frode Haug
|  220103  |  Updated for/to Standard C++.             |  Frode Haug
|  060116  |  A lot of name changes.                   |  Frode Haug
|  110216  |  Made this version for multifile projects.|  Frode Haug
|          |                                           |
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/       

#if !defined(__LISTTOOL2B_H)           //  Ensures that this file will be
#define __LISTTOOL2B_H                 //    included only ONCE in each file.


			     //  ENUM:
enum listtype  { LIFO, FIFO, Sorted }; //  Allowed list-types.


			     //  CLASSES:
class NumElement;                      //  Predeclaration.
class TextElement;                     //  Predeclaration.

			     
class Element  {                       //  Base class 'Element'.
  private:
    char elementType;                  //  Type of element: 'B'(ase), 
				                       //    'N'(umeric) or 'T'(ext).
    friend class NumElement;           //  Only these two classes can 
    friend class TextElement;          //    manipulate 'elementType'.

  public:
    Element();                         //  Sets element type.
    virtual ~Element();                //  Virtual, empty destr.
    char getType();                    //  Return element type.
    virtual int compare (Element* el); 
    virtual void display();            //  Displayed only if function is NOT
				       //   redefined insided derived classes.
};


class NumElement: public Element  {    //  Base class for all numeric 
  protected:                           //    sorted elements.
    int number;                        //  ID-number.

  public:
    NumElement();                      //  Needs and reads the ID-number.
    NumElement(int no);                //  Created with an ID.
    virtual int compare(Element* el);  //  Compares own number with  el's.
};


class TextElement: public Element  {   //  Base class for all text/string
  private:                             //   sorted elements.
    void strcpy2(char* s, const char* t);  //  Self-made "strcpy"

  protected:                           //    
    char* text;                        //  Pointer to ID-text/string.

  public:
    TextElement();                     //  Needs and reads the ID-name/text.
    TextElement(const char* t);        //  Created with an ID.
    ~TextElement();                    //  Deletes the text ID.
    virtual int compare(Element* el);  // Compares own name/text with el's.
};



class List  {                          //  The class 'List'.
  private:
    struct Node  {                     //  Internal struct 'node'.
      Element*  liElem;                //  Element from the program that
				                       //    is stored inside THIS node.
      Node*     next;                  //  Nodes are linked together.
    };

    Node*     first;                   //  Pointer to first element/head.
    Node*     last;                    //  Pointer to tail. Only relevant
				                       //    for sorted lists.
    listtype  liType;                  //  'LIFO', 'FIFO' or 'Sorted'.
    int       noInList;                //  Number of elements in the list.

    Node* findPosition(Element* eptr); //  Internal function. Used by
					                   //    several other functions.
  public:
    List();                            //  Constructors.
    List(listtype li);
    ~List();                           //  Destructor.

		//  15 functions available for the user/program
   	        //     (some of them are overloaded).
		//  For different type of lists are the following functions relevant:
		              					//  LIFO/FIFO   Num Sort   Text Sort
    bool isEmpty();                     //      X          X           X 
    int noOfElements();                 //      X          X           X
    bool add(Element* el);              //      X          X           X 
    Element* remove();                  //      X               
    Element* remove(int no);            //                 X
    Element* remove(const char* t);     //                             X
    Element* removeNo(int n);           //                 X           X
    bool destroy();                     //      X   
    bool destroy(int no);               //                 X
    bool destroy(const char* t);        //                             X
    bool inList(int no);                //                 X
    bool inList(const char* t);         //                             X
    bool displayElement(int no);        //      X          X
    bool displayElement(const char* t); //                             X
    void displayList();                 //      X          X           X
}; 


#endif
