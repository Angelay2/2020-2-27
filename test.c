#include <stdio.h>
#include <windows.h>
#include <malloc.h>

// 常见的动态内存错误
// 1.malloc申请成功之后 需要判断 判定成功才可以 申请失败返回为空
// 2.free完了之后 需把指针设置为空
void test1(){
	int*p = (int*)malloc(INT_MAX / 4);
	*p = 20;// 如果p的值时NULL, 就会有问题
	free(p);// 完了之后 需要把指针置为空
}
// 3.对动态开辟空间的越界访问
void test2(){
	int i = 0;
	int* p = (int*)malloc(10 * sizeof(int));
	if (NULL == p){
		exit(EXIT_FAILURE);// EXIT表示从这里直接退出
	}
	for (i = 0; i <= 10; i++){
		*(p + i) = i;// 当 i 是 10 时越界访问 申请了10个字节 但访问到11个字节
		// 数组元素的下一个元素允许访问 上面这里不允许(堆空间绝对不能越界)
	}
	free(p);
}
// 3.对非动态开辟内存使用free函数
// free只能释放在堆上开辟的空间 但是a是在栈上开辟的空间
// 因为他是在函数内部开辟 => 局部变量 => 就是在栈上开辟的 
// 且栈上的空间不需要我们来free, 由系统自己释放
void test3(){
	int a = 10;
	int* p = &a;
	free(p);// 错误
}
// 4.使用free释放一块动态开辟内存的一部分
// 堆空间必须整体申请 整体释放,不能释放局部
// 申请时告诉了空间大小 但free的时候并不知道free多少(大小) 只给了起始位置 
// 但是在你申请空间的时候 系统已经把你申请多少字节记录下来了
// 所以就需要堆内部一定有个参数表示空间 所以free一定会多释放
void test4(){
	int* p = (int*)malloc(100);
	p++;
// p不再指向动态内存的起始位置 系统会从此地址处往后释放之前指定大小的空间
	free(p);
}
// 5. 对同一块动态内存多次释放, 同时忘记判定NULL
// 向系统申请资源 资源有限(向爸妈要钱 , 有钱 和 没钱)
void test5(){
	int* p = (int*)malloc(100);
	free(p);
// 如果传了空指针 free就什么都没做 
// free的是指针与申请的堆空间的关系 指针的内容不会被改变或清空 
// 第一次free后之后p还是指向之前的堆空间 第二次free就会报错(因为关系已断)
	free(p);
}
// 6. 动态开辟内存忘记释放(内存泄漏)
// p是变量 在栈上开辟 malloc申请的空间是在堆上 p里放的是堆空间的地址
// 
void test6(){
	int* p = (int*)malloc(100);
	if (NULL != p){
		*p = 20;
	}// 忘记释放
}
int main(){
	test();
	while (1);
	system("Ppause");
	return 0;
}