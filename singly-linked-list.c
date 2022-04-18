#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("[----------------- [Cho Daehyeon] [2016039075] -----------------]\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 추가할 노드 생성
	node->key = key;	// 노드에 저장할 값 넣기
	node->link = NULL;	// 노드의 링크필드 초기화

	if (h->first == NULL)	// 첫 번째 노드가 공백일때
	{
		h->first = node;	// 첫 번째 노드에 새로 만든 노드 저장
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	while(n != NULL) {				// 마지막 노드까지 검사
		if(n->key >= key) {			// 입력받은 키가 n->key보다 작을 때
			if(n == h->first) {		// n이 첫 번째 노드일 때
				h->first = node;
				node->link = n;
			} else {				// 중간이나 뒤에 있을 때
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	trail->link = node;		// 마지막까지 찾지 못했을 경우 마지막에 노드 저장
	return 0;
}

int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 마지막에 저장할 노드 생성
	node->key = key;
	node->link = NULL;		// 마지막 노드의 링크필드는 null

	if (h->first == NULL)	// 리스트가 공백일 경우
	{
		h->first = node;	// 리스트의 첫 번째에 노드 삽입
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {	// 마지막 노드로 이동
		n = n->link;
	}
	n->link = node;			// 마지막 노드의 뒤에 생성한 노드 저장
	return 0;
}

int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 맨 앞에 저장할 노드 생성
	node->key = key;

	node->link = h->first;	// 기존의 맨 앞 노드를 가리키는 포인터 노드의 링크필드에 저장
	h->first = node;

	return 0;
}

int deleteNode(headNode* h, int key) {

	if (h->first == NULL)	// 삭제할 노드가 없을 때 메시지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) {		// 삭제할 노드가 맨 앞에 있을 때
				h->first = n->link;
			} else { 				// 삭제할 노드가 중간이나 뒤에 있을 때
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}
	printf("cannot find the node for key = %d\n", key); 	// 삭제할 노드를 못 찾았을 때
	return 0;

}

int deleteLast(headNode* h) {

	if (h->first == NULL)		// 삭제할 노드가 없을 때
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->link == NULL) {		// 연결리스트에 노드가 하나밖에 없을 때
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->link != NULL) {	// 맨 마지막 노드로 이동
		trail = n;
		n = n->link;
	}

	trail->link = NULL;		// 마지막 노드와 그 전 노드 링크 끊기
	free(n);				// 노드 삭제

	return 0;
}

int deleteFirst(headNode* h) {

	if (h->first == NULL)		// 삭제할 노드가 업을 때
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;			// 첫 번째 노드의 다음 노드로 포인터 옮기기
	free(n);					// 첫 번째 노드 삭제

	return 0;
}

int invertList(headNode* h) {


	if(h->first == NULL) {		// 공백 리스트일 때 메시지 출력
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;		// 링크를 역순으로 바꿀 노드 가리키는 포인터 생성
	listNode *trail = NULL;
	listNode *middle = NULL;

	/* 첫 번째 노드부터 역순 정렬 */
	while(n != NULL){
		trail = middle;			// middle이 가리키는 노드를 trail도 가리키도록 변경(trail을 한칸 앞으로 옮김)
		middle = n;				// n이 가리키는 노드를 middle도 가리키도록 변경
		n = n->link;			// n 한칸 앞으로 옮기기
		middle->link = trail;	// middle이 가리키고 있는 노드의 링크필드에 trail 주소 저장
	}

	h->first = middle;

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

