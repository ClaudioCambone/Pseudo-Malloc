# Pseudo-Malloc
This is a project developed for the Computer Engineering program at Sapienza University of Rome in September 2023

# Requirements 
The project consist in the creation of a pseudo malloc, using a buddy allocator for small requests and `mmap` for bigger requests.
The buddy allocator divides memory into fixed-size blocks, with each block having a size that is a power of 2. When a memory request is made, the allocator finds an appropriate-sized block to satisfy the request. If the size of the request is bigger than the Pagesize/4, it uses `mmap` to request a new memory page from the operating system.
