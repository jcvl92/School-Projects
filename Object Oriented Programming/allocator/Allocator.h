#ifndef Allocator_h
#define Allocator_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <new>       // new
#include <stdexcept> // invalid_argument

#define alloc_size(num) (num*sizeof(value_type) + sent_size)
#define sent_size (2*sizeof(size_type))

// ---------
// Allocator
// ---------

template <typename T, int N>
class Allocator {
    public:
        // --------
        // typedefs
        // --------

        typedef T                 value_type;

        typedef int               size_type;
        typedef std::ptrdiff_t    difference_type;

        typedef value_type*       pointer;
        typedef const value_type* const_pointer;

        typedef value_type&       reference;
        typedef const value_type& const_reference;

    public:
        // -----------
        // operator ==
        // -----------

        friend bool operator == (const Allocator&, const Allocator&) {
            return true;}

        // -----------
        // operator !=
        // -----------

        friend bool operator != (const Allocator& lhs, const Allocator& rhs) {
            return !(lhs == rhs);}

    private:
        // ----
        // data
        // ----

        char a[N];

        // -----
        // valid
        // -----

        /**
         * O(1) in space
         * O(n) in time
         * asserts that the allocator array is valid(that the sentinels match up)
		 * @return true if it is valid, false otherwise
         */
        bool valid () const {
			//check if the array is valid
			for(int i=0;i<N;)
			{
				//if the sentinel is 0 for some reason, go ahead and fail, following it is a very bad idea
				if(*reinterpret_cast<size_type*>(const_cast<char*>(a+i)) == 0) return false;
				//compare the sentinel values
				if(*reinterpret_cast<size_type*>(const_cast<char*>(a+i)) != *reinterpret_cast<size_type*>(const_cast<char*>(a+i+abs(*reinterpret_cast<size_type*>(const_cast<char*>(a+i)))+sizeof(size_type)))) return false;
				//move i to next pair of sentinels
				i += abs(*reinterpret_cast<size_type*>(const_cast<char*>(a+i)))+2*sizeof(size_type);
			}
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * O(1) in space
         * O(1) in time
         * initializes the data array(marks the array block as free)
         */
        Allocator () {
			assert(N >= alloc_size(1));
			//mark the two free sentinels
			view(a[0]) = N-sent_size;
			view(a[N-sizeof(size_type)]) = N-sent_size;

            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Allocator  (const Allocator<T>&);
        // ~Allocator ();
        // Allocator& operator = (const Allocator&);

        // --------
        // allocate
        // --------

        /**
         * O(1) in space
         * O(n) in time
         * allocates a block of the data array, if there is one available
		 * @param n a size_type that indicates the desired size of the block
		 * @return a pointer to the allocated block
         * after allocation there must be enough space left for a valid block
         * the smallest allowable block is sizeof(T) + (2 * sizeof(int))
         * choose the first block that fits
         */
        pointer allocate (size_type n) {
		//check the boundries
		if(n>(int)(N-sent_size)) throw std::bad_alloc();//allocation failed, boundry overflow

		//check for enough space to do the allocation
			int i;
			for(i=0;i<N;)
			{
				//look for a free block that fits
				if(view(a[i]) >= (int)(n*sizeof(value_type))) break;

				//move to the next pair of sentinels
				i += abs(view(a[i]))+2*sizeof(size_type);
			}

			if(i>=N) throw std::bad_alloc();//allocation failed, no free space

			//chop the block if there would be at least sizeof(T) + (2 * sizeof(int)) left, otherwise, overallocate
			if(view(a[i]) >= (int)((n*sizeof(value_type))+alloc_size(1)))
			{
				//set the free block
				view(a[i+(n*sizeof(value_type))+(2*sizeof(size_type))]) = view(a[i])-alloc_size(n);
				view(a[i+view(a[i])+sizeof(size_type)]) = view(a[i])-alloc_size(n);

				//set the used block
				view(a[i]) = ~(n*sizeof(value_type))+1;
				view(a[i+(n*sizeof(value_type))+sizeof(size_type)]) = ~(n*sizeof(value_type))+1;
			}
			else
			{
				//overallocate
				//flip the sentinel values, setting the free block to used
				view(a[i+view(a[i])+sizeof(size_type)]) = ~view(a[i])+1;
				view(a[i]) = ~view(a[i])+1;
			}

			assert(valid());
		return (pointer)(a+i+sizeof(size_type));}

        // ---------
        // construct
        // ---------

        /**
         * O(1) in space
         * O(1) in time
         * fills part of a block with a value
		 * @param p a pointer to the location in the block
		 * @param v a reference to the value to place in the block
         */
        void construct (pointer p, const_reference v) {
            new (p) T(v);
            assert(valid());}

        // ----------
        // deallocate
        // ----------

        /**
         * O(1) in space
         * O(1) in time
         * frees a previously allocated block, merges any free blocks together
		 * @param ptr a pointer to the beginning of the block to free
		 * @param size_type the size of the block(set to 0)
         * after deallocation adjacent free blocks must be coalesced
         */
        void deallocate (pointer ptr, size_type = 0) {
	char* p = reinterpret_cast<char*>(ptr);//cast the pointer as a character pointer so accessing the sentinels is easier

            //flip the sentinel values to mark them as free
			view(*(p+(~view(*(p-sizeof(size_type)))+1))) = ~view(*(p-sizeof(size_type)))+1;	//flip back sentinel
			view(*(p-sizeof(size_type))) = ~view(*(p-sizeof(size_type)))+1;			//flip front sentinel

			//merge with blocks behind and in front if they are free

			//don't look forward if at the end
			if(p+view(*(p-sizeof(size_type)))+sizeof(size_type) < a+N)
				//if the block in front of this one is free, merge the two blocks
				if(view(*(p+view(*(p-sizeof(size_type)))+sizeof(size_type))) > 0)
				{
					//change the value of the endpoint sentinels
					//change back sentinel
					view(*(p+view(*(p-sizeof(size_type)))+view(*(p+view(*(p-sizeof(size_type)))+sizeof(size_type)))+sent_size))
						= view(*(p-sizeof(size_type))) + view(*(p+view(*(p-sizeof(size_type)))+sizeof(size_type))) + sent_size;
					//change front sentinel
					view(*(p-sizeof(size_type)))
						= view(*(p-sizeof(size_type))) + view(*(p+view(*(p-sizeof(size_type)))+sizeof(size_type))) + sent_size;
					//middle sentinels are ignored and are now part of the block
				}

			//don't look back if at the beginning
			if(p-sent_size > a)
				//if the block behind this one is free, merge the two blocks
				if(view(*(p-sent_size)) > 0)
				{
					//change the value of the endpoint sentinels
					//change the back sentinel
					view(*(p+view(*(p-sizeof(size_type)))))
						= view(*(p-sent_size)) + view(*(p-sizeof(size_type))) + sent_size;
					//change the front sentinel
					view(*(p-sent_size-sizeof(size_type)-view(*(p-sent_size))))
						= view(*(p-sent_size)) + view(*(p-sizeof(size_type))) + sent_size;
					//middle sentinels are ignored and are now part of the block
				}

            assert(valid());}

        // -------
        // destroy
        // -------

        /**
         * O(1) in space
         * O(1) in time
         * deconstructs a previously constructed object
		 * @param p a pointer to the object
         */
        void destroy (pointer p) {
            p->~T();
            assert(valid());}

	int& view(char& c)
	{
		return *reinterpret_cast<size_type*>(&c);
	}
};

#endif // Allocator_h
