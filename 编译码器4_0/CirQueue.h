#define _CRT_SECURE_NO_WARNINGS
#ifndef CIRQUEUE_H
#define CIRQUEUE_H
#include <iostream>
#include <string>
#include "Base.h"
using namespace std;
const  int  QUEUE_SIZE = 1000000000;
template <class T>
class  CirQueue
{
public:
	CirQueue();
	~CirQueue() {
		delete[] data;
	};
	void EnQueue(T x);//入队
	void EnQueues(T *temp, int n);//八位一起入队列
	unsigned char get8Bites(bool i1);//弹出前八位并转化位一位unsigned char型元素
	T DeQueue();//删除元素
	T GetQueue();//获取栈顶元素
	bool  Empty() {//判断是否空队列
		if (front == rear&&flag==0)
			return 1;
		return 0;
	}
private:
	T* data;
	int front, rear;
	bool flag;
};
template  <class T>
CirQueue <T>::CirQueue()
{
	rear = front = QUEUE_SIZE - 1;
	flag=0;
	data=new T[QUEUE_SIZE];
}
template  <class T>
void CirQueue<T>::EnQueue(T x)
{
	if (rear == front&&flag == 1)throw"上溢";
	rear = (rear + 1) % QUEUE_SIZE;
	data[rear] = x;
	if (rear == front)
		flag = 1;
}
template  <class T>
T CirQueue<T>::DeQueue()
{
	if (rear == front&&flag == 0) { throw"下溢"; return 0; }
	front = (front + 1) % QUEUE_SIZE;
	if (rear == front)
		flag = 0;
	return data[front];
}
template  <class T>
T CirQueue<T>::GetQueue()
{
	if (rear == front&&flag == 0) { throw"下溢"; return 0; }
	int i = (front + 1) % QUEUE_SIZE;
	return data[i];
}
template  <class T>
unsigned char CirQueue<T>::get8Bites(bool i1)
{
	char Get8Bites[8] = { 0 };
	unsigned char buff1;
	int restCount = (rear + QUEUE_SIZE - front) % QUEUE_SIZE;//记录剩余编码的数量
	if (i1)
	{
		if ((rear + QUEUE_SIZE - front) % QUEUE_SIZE < 8)
			return NULL;
		for (int i = 0; i < 8; i++)
			Get8Bites[i] = DeQueue();
		getHex(buff1, Get8Bites, 0, 7);
	}
	else
	{
		if ((rear + QUEUE_SIZE - front) % QUEUE_SIZE < 8)
		{

			for (int i = 0; i < restCount; i++)
				Get8Bites[8-restCount+i] = DeQueue();
			getHex(buff1, Get8Bites, 0, 7);
			for (int i = 0; i < 8 - restCount; i++)
				buff1 = buff1 << 1;
		}
		else
		{
			for (int i = 0; i < 8; i++)
				Get8Bites[i] = DeQueue();
			getHex(buff1, Get8Bites, 0, 7);
		}
	}
	return buff1;
}
template  <class T>
void CirQueue<T>::EnQueues(T *temp, int n)
{
	for (int i = 0; i < n; i++)
	{
		EnQueue(temp[i]);
	}
}
#endif