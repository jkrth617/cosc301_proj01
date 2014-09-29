#include <stdio.h>
#include <stdlib.h>
#include "list.h"



void validity_create(struct node** head, char* token){
	int valid=1;
	int neg = 0;
	int j = 0;
	if(token[0]=='-'){
		j = 1;//skip the '-' in the for loop below
		neg=1;//set a boolean (used later)
	}
	for(j; j<= (strlen(token)-1); j++){
		int tester = isdigit(token[j]);
		if(tester==0){
			valid=0;//not valid
			break; //get out of for loop because its not an input
		}
	}
	if (valid==1){//no non numbers were found so valid wasnt changed
		int new_val=0;			
		if(neg==1){				
			token[0] = '0';//replace the - with 0 so it doesnt do anything to the number value
			new_val=atoi(token);
			new_val= new_val*(-1);//make it negative
		}			
		else{			
			new_val=atoi(token);//else just make it an int
		}
		LL_create_sort(head, new_val);
	}
return;
}


void LL_create_sort(struct node ** head, int new_val){
	if((*head)==NULL){//first time adding anything
		struct node* special = malloc(sizeof(struct node));
		special->val= new_val;
		special->next = NULL;			
		*head= special;
		return;
	}
	struct node* temp= *head;
	struct node* adding_node= malloc(sizeof(struct node));//create a new malloced adding node
	if (((*head)->val) > (new_val)){//head is bigger than the new one
		adding_node->val = new_val;
		adding_node->next=*head;
		*head=adding_node;//we have a new head!!			
	}
	else{
		while(temp!=NULL){
			if (temp->next==NULL){//got to the end i.e. its the biggest number
				temp->next = adding_node;
				adding_node->val = new_val;
				adding_node->next=NULL;
				break;
			}
			if(new_val < ((temp->next)->val)){//put it in the middle of the list
				struct node * pnext = temp->next;
				temp->next = adding_node;
				adding_node->val = new_val;
				adding_node->next=pnext;
				break;	
			}
			temp= temp->next;
		}
	}
	return;
}




void list_print(const struct node *list) {    
    while (list != NULL) {
        printf("%d\n", list->val);
        list = list->next;
    }
}

void list_destroy(struct node * head){
	struct node * kill = head;
	while (head != NULL){
		kill = head;
		head = head->next;
		free(kill);
	}
}
	

