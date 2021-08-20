
int allOn(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int allOff(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int chaser(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int chaserSingleColor(int seq_position, bool reverse, uint32_t colors[], int num_colors);

typedef int (*pfnSequence)(int seq_position, bool reverse, uint32_t colors[], int num_colors);

struct sequence {
        char * seq_name;            // Lower case - no spaces 
        char * title;               // Value to show to user
        char * description;         // Tool tip (if applicable)
        pfnSequence seqFunction;    // ptr to function
};

struct sequence sequences[] {
    { .seq_name = "alloff", .title = "All Off", .description = "Turn all LEDs off", .seqFunction = allOff},
    { .seq_name = "allon", .title = "All On", .description = "Turn all LEDs on", .seqFunction = allOn },
    { .seq_name = "chaser", .title = "Chaser", .description = "Chaser sequence", .seqFunction = chaser },
    { .seq_name = "chasersinglecolor", .title = "Chaser Single Color", .description = "Chaser sequence signal color block of 4", .seqFunction = chaserSingleColor }
    
};
