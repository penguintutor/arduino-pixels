/* Define sequences for arduino-pixels */
// All sequence functions must follow this format
// seq_position is the position in the sequence, this needs is defined as long for the UNO WiFi which would otherwise be limited to (2^8)/2

typedef long (*pfnSequence)(long seq_position, bool reverse, uint32_t colors[], int num_colors);

struct sequence {
        char * seq_name;            // Lower case - no spaces 
        char * title;               // Value to show to user
        char * description;         // Tool tip (if applicable)
        int group;                  // Group together sequences (allows some to be excluded) 0 = basic, 1 = common (some chasers etc.), 2 = extra, 4 = rare
        pfnSequence seqFunction;    // ptr to function
};


// define all sequences here. All these parameters are required even if the sequence doesn't use them (eg. allOff does not use colors or num_colors)
long allOn(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long allOff(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long flash(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long chaser(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long chaserChangeColor(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long chaserBackground(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long chaserFillEnd(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long colorWipeOn(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long colorWipeOff(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long colorWipeOnOff(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long colorWipeInOn(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long colorWipeOutOn(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long colorWipeInOff(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long colorWipeOutOff(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long colorWipeInOut(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long colorWipeOutIn(long seq_position, bool reverse, uint32_t colors[], int num_colors);
long rainbow(long seq_position, bool reverse, uint32_t colors[], int num_colors);

// Add new sequences to this structure. This is used for web page to know what options are available
// The group argument can be used to group certain sequences together (eg. to only show certain sequences or display on a different tab)
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
    { .seq_name = "colorwipeoutin", .title = "Color Wipe Out in", .description = "Turn on in sequence going outwards, then out again. Starting at both ends.", .group = 3, .seqFunction = colorWipeOutIn },
    { .seq_name = "rainbow", .title = "Rainbow sequence", .description = "Display a rainbow color sequence which moves along the lights.", .group = 3, .seqFunction = rainbow }
};
