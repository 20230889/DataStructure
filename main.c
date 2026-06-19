#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;           // 데이터
    struct Node* next;  // 다음 노드의 주소
} Node;

// 첫 번째 노드 삽입 함수
Node* insertFirst(Node* head, int data) {
    // 새로운 노드 생성
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL; // 새로운 노드는 초기에는 아무것도 가리키지 않음

    // Head가 NULL인 경우 (리스트가 비어 있음)
    if (head == NULL) {
        return newNode; // 새 노드가 리스트의 시작점이 됨
    }

    // Head가 NULL이 아닌 경우 (리스트에 기존 노드가 있음)
    newNode->next = head; // 새 노드의 다음을 기존 Head로 연결
    return newNode;       // 새 노드를 Head로 설정
}

// 마지막에 노드 추가 함수
Node* insertLast(Node* head, int data) {
    // 새로운 노드 생성
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL; // 새 노드는 리스트의 끝을 나타냄

    // 리스트가 비어 있는 경우
    if (head == NULL) {
        return newNode; // 새 노드가 리스트의 시작점이 됨
    }

    // 리스트에 기존 노드가 있는 경우
    Node* current = head;
    while (current->next != NULL) { // 마지막 노드를 찾음
        current = current->next;
    }
    current->next = newNode; // 마지막 노드의 next에 새 노드를 연결

    return head; // 리스트의 시작점(head) 반환
}

// 특정 값을 가진 노드 뒤에 삽입
void insertAfterValue(Node* head, int targetValue, int newData) {
    Node* current = head;

    // 노드 탐색
    while (current != NULL) {
        if (current->data == targetValue) {
            // 새 노드 생성 및 삽입
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->data = newData;
            newNode->next = current->next;
            current->next = newNode;
            return;
        }
        current = current->next;
    }

    // 값이 일치하는 노드가 없을 경우
    printf("값 %d를 가진 노드를 찾을 수 없습니다. 삽입하지 않습니다.\n", targetValue);
}

// 1. 헤드 노드 삭제 함수
Node* deleteHead(Node* head) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다. 삭제할 노드가 없습니다.\n");
        return NULL;
    }

    Node* temp = head;     // 현재 헤드 노드를 임시 저장
    head = head->next;     // 헤드를 다음 노드로 변경
    free(temp);            // 이전 헤드 메모리 해제

    return head;
}

// 2. 마지막 노드 삭제 함수
Node* deleteLast(Node* head) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다. 삭제할 노드가 없습니다.\n");
        return NULL;
    }

    if (head->next == NULL) { // 리스트에 노드가 하나만 있는 경우
        free(head);
        return NULL;
    }

    Node* current = head;
    while (current->next->next != NULL) { // 마지막에서 두 번째 노드 찾기
        current = current->next;
    }

    free(current->next);    // 마지막 노드 메모리 해제
    current->next = NULL;   // 이전 노드의 next를 NULL로 설정

    return head;
}

// 3. 특정 값의 노드 삭제 함수
Node* deleteNode(Node* head, int targetValue) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다. 삭제할 노드가 없습니다.\n");
        return NULL;
    }

    if (head->data == targetValue) { // 헤드 노드가 대상 값인 경우
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node* current = head;
    while (current->next != NULL && current->next->data != targetValue) {
        current = current->next;
    }

    if (current->next == NULL) { // 대상 값을 찾지 못한 경우
        printf("값 %d를 가진 노드를 찾을 수 없습니다.\n", targetValue);
        return head;
    }

    Node* temp = current->next;  // 삭제할 노드
    current->next = current->next->next; // 링크 재조정
    free(temp);                   // 삭제할 노드 메모리 해제

    return head;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("모든 노드가 제거되었습니다.\n");
}

int searchValue1(Node* head, int val) {
    if (head == NULL) {
        printf("Head Node가 NULL 입니다.\n");
        return -1;
    }
    Node* current = head;
    int pos = 0;
    while (current != NULL) {
        ++pos;
        if (current->data == val) return pos;
        else current = current->next;
    }
    printf("값이 없습니다.\n");
    return -1;
}

void searchValue2(Node* head, int val) {
    if (head == NULL) {
        printf("Head Node가 NULL 입니다.\n");
        return;
    }
    if (head->data == val) {
        printf("%d의 이전값 : 없음\n", val);
        printf("%d의 다음값 : %d\n", val, head->next->data);
        return;
    }
    Node* current = head;
    while (current->next != NULL && current->next->data != val) {
        current = current->next;
    }
    if (current->next == NULL) {
        printf("%d를 찾을 수 없습니다.\n", val);
        return;
    }
    printf("%d의 이전 값 : %d\n", val, current->data);
    printf("%d의 다음 값 : %d\n", val, current->next->next->data);
}

int main() {
    Node* head = NULL;
    
    for (int i=0; i<10; i++) {
        head = insertLast(head, i);
    }
    // 실습 1-4: printList 테스트
    printf("=== 리스트 출력 ===\n");
    printList(head);

    // 실습 1-5: searchValue1 테스트
    printf("\n=== searchValue1 테스트 ===\n");
    int pos = -1;
    int val = 5;
    pos = searchValue1(head, val);
    if (pos != -1) {
        printf("%d의 위치는 %d번째\n", val, pos);
    }
    
    // 실습 1-5: searchValue2 테스트
    printf("\n=== searchValue2 테스트 ===\n");
    searchValue2(head, 5);

    // freeList 테스트
    printf("\n=== freeList 테스트 ===\n");
    freeList(head);
    
    return 0;
}