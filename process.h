typedef enum process_state {
    READY,
    RUNNING
} process_state_t;

typedef struct process_context {
    int eax;
    int ecx;
    int edx;
    int ebx;
    int esp;
    int ebp;
    int esi;
    int edi;
    int eip;
} process_context_t;

typedef struct process {
    int pid;
    process_context_t context;
    process_state_t state;
    int* base_address;
} process_t;

process_t* processes[15];
int process_count;
int curr_pid;

void process_init();
process_t* process_create(int*);