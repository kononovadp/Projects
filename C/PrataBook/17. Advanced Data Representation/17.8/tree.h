// tree.h -- двоичное дерево поиска                            
//           дублированные элементы в этом дереве не разрешены 
#ifndef _TREE_H_
#define _TREE_H_
#include <stdbool.h>
#include "tree.c"

// прототипы функций 

// операция:     инициализация дерева пустым содержимым 
// предусловия:  ptree указывает на дерево              
// постусловия:  дерево установлено в пустое состояние  
void InitializeTree(Tree * ptree);

// операция:     определение, является ли дерево пустым 
// предусловия:  ptree указывает на дерево              
// постусловия:  функция возвращает true, если дерево   
//               пустое, и false – в противном случае   
bool TreeIsEmpty(const Tree * ptree);

// операция:     определение, является ли дерево полным 
// предусловия:  ptree указывает на дерево              
// постусловия:  функция возвращает true, если дерево   
//               полное, и false – в противном случае   
bool TreeIsFull(const Tree * ptree);

// операция:     определение количества элементов в дереве        
// предусловия:  ptree указывает на дерево                        
// постусловия:  функция возвращает количество элементов в дереве 
int TreeItemCount(const Tree * ptree);

// операция:     добавление элемента к дереву                 
// предусловия:  pi – адрес добавляемого элемента             
//               ptree указывает на инициализированное дерево 
// постусловия:  если возможно, функция добавляет элемент     
//               к дереву и возвращает true;                  
//               в противном случае она возвращает false      
bool AddItem(const Item * pi, Tree * ptree);

// операция:     поиск элемента в дереве                            
// предусловия:  pi указывает на элемент                            
//               ptree указывает на инициализированное дерево       
// постусловия:  функция возвращает true, если элемент присутствует 
//               в дереве, и false – в противном случае             
bool InTree(const Item * pi, const Tree * ptree);

// операция:     удаление элемента из дерева                      
// предусловия:  pi – адрес удаляемого элемента                   
//               ptree указывает на инициализированное дерево     
// постусловия:  если возможно, функция удаляет элемент из дерева 
//               и возвращает true; в противном случае функция    
//               возвращает false                                 
bool DeleteItem(const Item * pi, Tree * ptree);

// операция:     применение указанной функции к каждому элементу в дереве 
// предусловия:  ptree указывает на дерево                                
//               pfun указывает на функцию, которая принимает             
//               аргумент Item и не имеет возвращаемого значения          
// постусловия:  функция, указанная с помощью pfun, выполняется один раз  
//               для каждого элемента в дереве                            
void Traverse (const Tree * ptree, void (* pfun)(Item item));

// операция:     удаление всех элементов из дерева            
// предусловия:  ptree указывает на инициализированное дерево 
// постусловия:  дерево является пустым                       
void DeleteAll(Tree * ptree);

#endif

