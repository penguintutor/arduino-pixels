
int allOn(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int allOff(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int flash(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int chaser(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int chaserChangeColor(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int chaserBackground(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int chaserFillEnd(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeOn(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeOff(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeOnOff(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeInOn(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeOutOn(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeInOff(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeOutOff(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeInOut(int seq_position, bool reverse, uint32_t colors[], int num_colors);
int colorWipeOutIn(int seq_position, bool reverse, uint32_t colors[], int num_colors);


typedef int (*pfnSequence)(int seq_position, bool reverse, uint32_t colors[], int num_colors);

struct sequence {
        char * seq_name;            // Lower case - no spaces 
        char * title;               // Value to show to user
        char * description;         // Tool tip (if applicable)
        int group;                  // Group together sequences (allows some to be excluded) 0 = basic, 1 = common (some chasers etc.), 2 = extra, 4 = rare
        pfnSequence seqFunction;    // ptr to function
};

struct sequence sequences[] {
    { .seq_name = "alloff", .title = "All Off", .description = "Turn all LEDs off", .group = 0, .seqFunction = allOff},
    { .seq_name = "allon", .title = "All On", .description = "Turn all LEDs on", .group = 0, .seqFunction = allOn },    
    { .seq_name = "flash", .title = "Flash", .description = "Flash all LEDs on and off together", .group = 0, .seqFunction = flash },
    { .seq_name = "chaser", .title = "Chaser", .description = "Chaser sequence", .group = 0, .seqFunction = chaser },
    { .seq_name = "chaserchangecolor", .title = "Chaser Change Color", .description = "Chaser sequence color block of 4, changing to each color in turn", .group = 1, .seqFunction = chaserChangeColor },
    { .seq_name = "chaserbackground", .title = "Chaser Solid Background", .description = "Chaser sequence one block of colour across black background", .group = 1, .seqFunction = chaserBackground },
    { .seq_name = "chaserfillend", .title = "Chaser Fill End", .description = "Single LED chaser to end and then fill up", .group = 1, .seqFunction = chaserFillEnd },
    { .seq_name = "colorwipeon", .title = "Color Wipe On", .description = "From first pixel to last pixel add LED at a time then stay lit", .group = 2, .seqFunction = colorWipeOn },
    { .seq_name = "colorwipeoff", .title = "Color Wipe Off", .description = "From all on remove LED at a time then stay off", .group = 2, .seqFunction = colorWipeOff },
    { .seq_name = "colorwipeonoff", .title = "Color Wipe On Off", .description = "Turn on in sequence, then off again", .group = 1, .seqFunction = colorWipeOnOff },
    { .seq_name = "colorwipeinon", .title = "Color Wipe In On", .description = "Turn on from outside to center. Starting at both ends.", .group = 4, .seqFunction = colorWipeInOn },
    { .seq_name = "colorwipeouton", .title = "Color Wipe Out On", .description = "Turn on from center to outside. Starting at both ends.", .group = 4, .seqFunction = colorWipeOutOn },
    { .seq_name = "colorwipeinoff", .title = "Color Wipe In Off", .description = "Turn off from outside to center. Starting at both ends.", .group = 4, .seqFunction = colorWipeInOff },
    { .seq_name = "colorwipeoutoff", .title = "Color Wipe Out Off", .description = "Turn off from center to outside. Starting at both ends.", .group = 4, .seqFunction = colorWipeOutOff },
    { .seq_name = "colorwipeinout", .title = "Color Wipe In Out", .description = "Turn on in sequence going inwards, then out again. Starting at both ends.", .group = 3, .seqFunction = colorWipeInOut },
    { .seq_name = "colorwipeoutin", .title = "Color Wipe Out in", .description = "Turn on in sequence going outwards, then out again. Starting at both ends.", .group = 3, .seqFunction = colorWipeOutIn }
};
