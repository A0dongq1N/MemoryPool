#ifndef __StackAlloc__
#define __StackAlloc__

#include <memory>

template <typename T>
struct StackNode_
{
	T data;
	StackNode_* prev;
};

template <typename T,typename Alloc = std::allocator<T> >
class StackAlloc
{
	public:
	    typedef StackNode_<T> Node;
		typedef typename Alloc::template rebind<Node>::other allocator;

    	StackAlloc()
		{
			head_ = 0;
		}
		
		~StackAlloc()
		{
			clear();
		}
		
		//return true if stack is empty
		bool empty()
		{
			return (head_ == 0);
		}
		
		void clear()
		{
			Node* curr = head_;
                        Node* tmp;
			while(curr != NULL)
			{
				tmp = curr->prev;
				allocator_.destroy(curr);
				allocator_.deallocate(curr,1);
				curr = tmp;
			}
			head_ = 0;
		}
		
		void push(T element)
		{
			Node* newnode = allocator_.allocate(1);
			allocator_.construct(newnode,Node());
			newnode->data = element;
			newnode->prev = head_;
		    head_ = newnode;
		}
		
		T pop()
		{
			T result = head_->data;
			Node* tmp = head_;
			head_ = head_->prev;
			allocator_.destroy(tmp);
			allocator_.deallocate(tmp,1);
			return result;
		}
		
		T top()
		{
			return head_->data;
		}
		
		private:
		    allocator allocator_;
			Node* head_;
};
#endif

