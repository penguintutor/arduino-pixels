
int allOn(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int allOff(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int chaser(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int chaserChangeColor(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int chaserBackground(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeOn(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeOff(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeOnOff(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeInOut(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeOutIn(int seq_position, bool reverse, uint32_t colors[], int num_colors);

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
    { .seq_name = "chaserchangecolor", .title = "Chaser Change Color", .description = "Chaser sequence color block of 4, changing to each color in turn", .seqFunction = chaserChangeColor },
    { .seq_name = "chaserbackground", .title = "Chaser Solid Background", .description = "Chaser sequence one block of colour across black background", .seqFunction = chaserBackground },
    { .seq_name = "colorwipeon", .title = "Color Wipe On", .description = "From first pixel to last pixel add LED at a time then stay lit", .seqFunction = colorWipeOn },
    { .seq_name = "colorwipeoff", .title = "Color Wipe Off", .description = "From all on remove LED at a time then stay off", .seqFunction = colorWipeOff },
    { .seq_name = "colorwipeonoff", .title = "Color Wipe On Off", .description = "Turn on in sequence, then off again", .seqFunction = colorWipeOnOff },
    { .seq_name = "colorwipeinout", .title = "Color Wipe In Out", .description = "Turn on in sequence going inwards, then out again. Starting at both ends.", .seqFunction = colorWipeInOut },
    { .seq_name = "colorwipeoutin", .title = "Color Wipe Out in", .description = "Turn on in sequence going outwards, then out again. Starting at both ends.", .seqFunction = colorWipeOutIn }
};
