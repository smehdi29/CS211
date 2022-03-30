
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// very incomplete small test program...

int main() {
	LIST *lst1;
	int i;

  	lst1 = lst_create();

  	for(i=0; i<5; i++) {
     		lst_push_front(lst1, i);
  	}
  	for(i=0; i<5; i++) {
     		lst_push_back(lst1, i);
  	}

  	printf("lst_length(lst1) : %i\n", lst_length(lst1));
  	printf("lst1 contents: ");
  	lst_print(lst1);


  	lst_pop_front(lst1);
  	lst_pop_front(lst1);
  	printf("lst1 contents after two pops: ");
 	lst_print(lst1);



  /** TODO:  test code here! **/

	/*THE FOLLOWING CODE REPLICATES A LST1 AND TESTS LST_ARE_EQUAL()*/

	LIST *lst2;
	lst2 = lst_create();
	for (i=0; i<5; i++) {
                lst_push_front(lst2, i);
        }
        for(i=0; i<5; i++) {
                lst_push_back(lst2, i);
        }

        printf("lst_length(lst2) : %i\n", lst_length(lst2));
        printf("lst2 contents: ");
        lst_print(lst2);


        lst_pop_front(lst2);
        lst_pop_front(lst2);
	
	printf("lst2 contents after three pops: ");
	lst_print(lst2);
	printf("Are lists equal? %i\n", lst_are_equal(lst1, lst2));//should print 1 (if you remove the last pop)
	lst_pop_front(lst2);
	lst_pop_front(lst2);//added to have a sorted list
	printf("lst 2 contents after one more pop: ");
	lst_print(lst2);
	printf("Are lists equal? %i\n", lst_are_equal(lst1,lst2));//should print 0

	//TEST for insert sorted
	printf("Insert 2 in list 2\n");
       	lst_insert_sorted(lst2, 2);
	lst_print(lst2);
	printf("Insert 5 in list 2\n");
        lst_insert_sorted(lst2, 5);
        lst_print(lst2);
	printf("Insert -1 in list 2\n");
	lst_insert_sorted(lst2, -1);
	lst_print(lst2);

	//TEST for lst_pop_back
	printf("Element popped back in lst1: %i\n",lst_pop_back(lst1));
	printf("New list 1: ");
	//lst_print(lst1);

	//TEST for merge sorted
	lst_pop_front(lst1);
	lst_pop_front(lst1);//these pops are to sort lst1
	lst_print(lst1);
	printf("Lst 2:");
	lst_print(lst2);
	lst_merge_sorted(lst1,lst2);
	printf("List 1 and 2 merged: ");
	lst_print(lst1);	
	
	//test for lst_reverse()
	lst_reverse(lst1);
	printf("Reversed list 1: ");
	lst_print(lst1);


  /** test code for lst_count **/

 	printf("number of 3's = %i\n", lst_count(lst1, 3));
  	printf("number of 0's = %i\n", lst_count(lst1, 0));


  /** test code for lst_print_rev **/
	printf("Lists printed reverse: \nList 1: ");
	lst_print_rev(lst1);
	printf("Removed 2s fast:\nList 1: ");
	printf("\n2s removed: %i\n", lst_remove_all_fast(lst1,2));
	lst_print(lst1);

	//COMMENTED OUT BECAUSE OF MERGE_SORTED() TEST (these tests worked)
	//lst_prefix() test
	/*
	LIST* lst3 = lst_prefix(lst2, 4);
	printf("List 2 Prefix of 4:");
	lst_print(lst3);
	printf("New list 2:");
	lst_print(lst2);
	LIST *lst4 = lst_filter_leq(lst2, 3);
	printf("List 2 after filtered for leq 3");
	lst_print(lst2);
	printf("List of removed: ");
	lst_print(lst4);
	printf("Concatenate lst 2 and 4: ");
	lst_concat(lst2,lst4);
	lst_print(lst2);
	*/ 






  /** test code for lst_push_back **/

  lst_free(lst1);
  //lst_free(lst2);//removed because lst_merge_sorted frees already
  //lst_free(lst3);
  //lst_free(lst4); //freed in lst_concat()
}
  
