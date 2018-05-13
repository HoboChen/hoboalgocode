/*
   @title: Cartesian Tree 笛卡尔树
   @description:
   Cartesian Tree 笛卡尔树
   可以实现线性时间内建立具有BST性质的树
   @structure:
CartesianTreeNode:
parent:　父指针
l: 左孩子指针
r: 右孩子指针
@arguments:
BuildFromArray:
value: 源数组
N: 数组大小
index: 源数组的逆映射数组
tree: 目标建树数组内存首地址
stack: 堆栈空间
@performance:
BuildFromArray:
Time: O(N)
Space: O(N)
@dependence: null
@range:
for i in [0, N)
value[i] in [0, N)
index[i] in [0, N)
|value| = |index| = |tree| = |stack| = N
@note:
value 与 index 互为逆映射故满足双射性质
index[value[i]] == i
value[index[i]] == i
index 无须在函数外初始化，建树过程可以计算 index
stack 无须在函数外初始化，但建树过程对 stack 有污染
最后结束迭代的时候栈底一定为 value[0]
笛卡尔树的树根一定为 value[0]
因此笛卡尔树的 parent 不一定要保存，仅保存孩子指针也可以完成遍历
*/

struct CartesianTreeNode {
	int parent, left, right;
};

void BuildFromArray(int *value, int N, int *index, CartesianTreeNode *tree, int *stack) {
	// 计算逆映射
	for (int i = 0; i < N; i++) {
		index[value[i]] = i;
	}
	// 初始化节点
	for (int i = 0; i < N; i++) {
		tree[i].parent = tree[i].left = tree[i].right = -1;
	}
	int size = 0; // 初始化清空栈
	for (int i = 0; i < N; i++) {
		int nextSize = size;
		// 维护单调栈
		while (nextSize > 0 && index[stack[nextSize - 1]] > index[i]) {
			nextSize--;
		}
		// 下面两个 if 语句块的顺序可变
		if (nextSize > 0) { // 栈中有元素
			// 当前元素为栈顶元素的右孩子
			int top = stack[nextSize - 1];
			tree[i].parent = top;
			tree[top].right = i;
		}
		if (nextSize < size) { // 弹过栈
			// 最后出栈的元素为当前元素的左孩子
			int lastPop = stack[nextSize];
			tree[lastPop].parent = i;
			tree[i].left = lastPop;
		}
		stack[nextSize++] = i; // 入栈
		size = nextSize;       // 更新栈大小
	}
}

