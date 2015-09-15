/* 
 * ------------------------------------------------------------------------
 *
 *                                      cdl_list.h
 *                                        V 0.01
 *
 *                             (c) Brian Lynch September, 2015
 *
 * ------------------------------------------------------------------------
 */

#ifndef cdl_list_h
#define cdl_list_h

#include <stdlib.h>
#include <iterator>

//! \class coplaDlost
template< class type >
class cdlList{
   
   public:
   
      //! \struct DlistNode
      struct DlistNode{
         
         public:
            
            DlistNode(const type &in_data, DlistNode *in_next = NULL,
                                          DlistNode *in_prev = NULL):
                       data(in_data), next(in_next), prev(in_prev){};
                                
            DlistNode *next;   //!< points to the next node in the Dlist
            DlistNode *prev;   //!< point to the previous node in the Dlist
            type data; //!< points to the data contained at the current node
         
      };
   
      int count;       //!< number of elements in the Dlist
      DlistNode *root; //!< sentinel root node of Dlist
      friend class iterator;
   
      //! \class iterator
      class iterator{
                                                
         public:
         
            DlistNode* itr_node;
         
            friend class cdlList<type>;
         
            iterator(DlistNode *in_node = NULL){
               itr_node = in_node;
            }
            
            //inline iterator(const iterator &in_itr):itr_node(in_itr.itr_node){}
            
            //Destructor needs no implementation
            ~iterator(){}
      
            //Assignment operator
            /* Note the const in the following operators. This is necessary
             * because only l-values can be bound to non-const references. Temporary
             * objects are rvalue and they can't be bound to non-const references. So,
             * for example, when binding a temporary object (i.e. begin() or end()) to
             * a reference to const on the stack, the lifetime of the temporary object
             * is extended to the lifetime of the const reference itself.
             */
            iterator& operator=(const iterator &rhs){
               itr_node = rhs.itr_node;
               return(*this);
            }
      
            //Equality operator
            bool operator==(const iterator &rhs){
               return(itr_node == rhs.itr_node);
            }
         
            //Inequality operator
            bool operator!=(const iterator &rhs){
               return(!(itr_node == rhs.itr_node));
            }
      
            //Prefix increment operator
            iterator& operator++(){
               itr_node = itr_node->next;
               return(*this);
            }
            
            //Prefix decrement operator
            iterator& operator--(){
               itr_node = itr_node->prev;
               return(*this);
            }
      
            //Postfix increment operator
            iterator operator++(int){
               iterator tmp(itr_node);
               itr_node = itr_node->next;
               return(tmp);
            }
            
            //Postfix decrement operator
            iterator operator--(int){
            
               iterator tmp(*this);
               itr_node = itr_node->prev;
               return(tmp);
            
            }
      
            //Return a reference to the value in the node for updating
            DlistNode& operator*(){
            
               return(*itr_node);
            
            }
      
            DlistNode* operator->(){
            
               return(itr_node);
            
            }
         
      };//End iterator class
   
      //Get iterator to beginning or list
      iterator begin(){
      
         return(iterator(root->next));
      
      }
   
      //Get iterator to end of list
      iterator end(){
      
         return(iterator(root));
      
      }
   
      //Constructor malloc's root node and sets it circular
      cdlList();
      
      //Deep copy constructor
      cdlList(const cdlList &rhs);
      
      //Destructor clears list and free's root node
      ~cdlList();

      //Clear cdlList
      void clear();
   
      //Check if cdlList is empty
      bool empty();
   
      //Insert a node containing data BEFORE the iterator
      void insert_before(iterator &itr, type &in_data);
   
      //Insert a node containing data AFTER the iterator
      void insert_after(iterator &itr, type &in_data);
    
      //Erase a node
      void erase(iterator &itr);
   
      //Add a node containing data to the back of list
      void push_back(type &data);
   
      //Add a node containing data to the front of list
      void push_front(type &data);

      //Erase the end node of Dlist
      void pop_back();
   
      //Erase the end node of Dlist
      void pop_front();
   
};

/*****************************************************************************/
/**
 * cdlList constructor implementation. Creates only the sentinel node
 *
 * @return void
 *
 */
template< class type >
cdlList<type>::cdlList(){//:root(DlistNode(type())),count(0){
   
   root = new DlistNode(type());
   root->prev = root;
   root->next = root;
   count = 0;
   
}//End cdlList constructor

/*****************************************************************************/
/**
 * cdlList destructor implementation. This function destroys cdlList
 *
 * @return void
 *
 */
template< class type >
cdlList<type>::~cdlList(){
   
   clear();
   delete root;
   
}

/*****************************************************************************/
/**
 * cdlList empty(...) implementation. This function tells whether or not
 * the list is empty.
 *
 * @return bool
 *
 */
template< class type >
bool cdlList<type>::empty(){
   
   return( root == root->next );
   
}

/*****************************************************************************/
/**
 * cdlList clear(...) implementation. This function destroys cdlList.
 *
 * @return void
 *
 */
template< class type >
void cdlList<type>::clear(){
   
   while( !empty() ){
      pop_back();
   }
   
   return;
   
}

/*****************************************************************************/
/**
 * cdlList insert_before(...) implementation. This function inserts into
 * cdlList BEFORE the location of the iterator.
 * 
 * @return void
 *
 */
template< class type >
void cdlList<type>::insert_before(iterator &itr, type &in_data){
   
   cdlList::DlistNode* tmp = new DlistNode(in_data,itr.itr_node,
                                              itr.itr_node->prev);
   
   //Check if only the root node exists
   if( itr.itr_node == root->prev ){
      itr.itr_node->prev = tmp;
   }
   
   //Re-route the pointers
   itr.itr_node->prev = tmp;
   tmp->prev->next = tmp;
   
   ++count;
   
   return;
   
}

/*****************************************************************************/
/**
 * cdlList insert_after(...) implementation. This function inserts into
 * cdlList AFTER the location of the iterator.
 * 
 * @return void
 *
 */
template< class type >
void cdlList<type>::insert_after(iterator &itr, type &in_data){
   
   cdlList::DlistNode* tmp = new DlistNode(in_data,itr.itr_node->next,
                                              itr.itr_node);
   
   //Check if only the root node exists
   if( itr.itr_node == root->prev ){
      itr.itr_node->next = tmp;
   }
   
   //Re-route the pointers
   itr.itr_node->next = tmp;
   tmp->next->prev = tmp;
   
   ++count;
   
   return;
   
}

/*****************************************************************************/
/**
 * cdlList push_back(...) implementation. This function adds a node
 * to the back.
 *
 * @param[in] data pinfo structure containing data to be copied into the new node
 *
 * @return void
 *
 */
template< class type >
void cdlList<type>::push_back(type &data){
   
   cdlList::iterator itr_end = end();
   insert_before(itr_end,data);
   
   return;
   
}

/*****************************************************************************/
/**
 * cdlList push_front(...) implementation. This function adds a node
 * to the front node of the list.
 *
 * @param[in] data pinfo structure containing data to be copied
 *
 * @return void
 *
 */
template< class type >
void cdlList<type>::push_front(type &data){
   
   cdlList::iterator itr_begin = begin();
   insert_before(itr_begin,data);
   
   return;
   
}

/******************************************************************************/
/**
 * cdlList pop_back(...) implementation. This function deletes the
 * back node of the list
 *
 * @return void
 *
 */
template< class type >
void cdlList<type>::pop_back(){
   
   iterator itr(--end()); //Increment back since end() is the root node
   erase(itr);
   
   return;
   
}

/******************************************************************************/
/**
 * cdlList pop_front(...) implementation. This function deletes the
 * front node of the list
 *
 * @return void
 *
 */
template< class type >
void cdlList<type>::pop_front(){
   
   iterator itr(begin());
   erase(itr);
   
   return;
}

/*****************************************************************************/
/**
 * cdlList erase(...) implementation. This function deletes a node
 * pointed at by itr
 *
 * @param[in] &itr iterator
 *
 * @return void
 *
 */
template< class type >
void cdlList<type>::erase(iterator &itr){
   
   //Make sure the root node is not deleted
   if( itr.itr_node == root ){
      return;
   }
   
   DlistNode* tmp = itr.itr_node; //Store the node
   itr.itr_node = tmp->prev;      //Move iterator back so its still valid
   
   //Re-route the pointers around the node to be deleted
   tmp->prev->next = tmp->next;  
   tmp->next->prev = tmp->prev;
   delete tmp;
   
   --count;
   
   return;
   
}

#endif