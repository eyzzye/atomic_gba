import sys

tile_indexes = []

def read_tile_indexes(filename):
    found_rodata_cnt = 0
    total_index = 0
    with open(filename) as file:
        for line in file:
            #print(line.rstrip())
            if found_rodata_cnt < 2:
                if ".section .rodata" in line:
                    found_rodata_cnt += 1
            elif found_rodata_cnt == 2:
                if ".hword" in line:
                    line_no_newline = line.rstrip()
                    #print(line_no_newline[8:])
                    data_list = line_no_newline[8:].split(",")
                    for index in data_list:
                        tile_indexes.append(index)
                        total_index += 1
                elif ".section .rodata" in line:
                    break
                else:
                    #print("skip")
                    pass
    #print(total_index)
    #print(tile_indexes)

def get_wall_tile():
    print("#define WALL_TILE1 ({})".format(tile_indexes[0]))
    print("#define WALL_TILE2 ({})".format(tile_indexes[1]))
    print("#define WALL_TILE3 ({})".format(tile_indexes[32]))
    print("#define WALL_TILE4 ({})".format(tile_indexes[33]))

def get_message():
    for i in range(0,11):
        print("#define MSG_TILE{}_1 ({})".format(i,tile_indexes[64+i*2]))
        print("#define MSG_TILE{}_2 ({})".format(i,tile_indexes[65+i*2]))
        print("#define MSG_TILE{}_3 ({})".format(i,tile_indexes[96+i*2]))
        print("#define MSG_TILE{}_4 ({})".format(i,tile_indexes[97+i*2]))
        print("#define MSG_TILE{}_5 ({})".format(i,tile_indexes[128+i*2]))
        print("#define MSG_TILE{}_6 ({})".format(i,tile_indexes[129+i*2]))
        print("#define MSG_TILE{}_7 ({})".format(i,tile_indexes[160+i*2]))
        print("#define MSG_TILE{}_8 ({})".format(i,tile_indexes[161+i*2]))

def get_yes():
    for i in range(0,3):
        print("#define YES_TILE{}_1 ({})".format(i,tile_indexes[192+i*2]))
        print("#define YES_TILE{}_2 ({})".format(i,tile_indexes[193+i*2]))
        print("#define YES_TILE{}_3 ({})".format(i,tile_indexes[224+i*2]))
        print("#define YES_TILE{}_4 ({})".format(i,tile_indexes[225+i*2]))
        print("#define YES_TILE{}_5 ({})".format(i,tile_indexes[256+i*2]))
        print("#define YES_TILE{}_6 ({})".format(i,tile_indexes[257+i*2]))
        print("#define YES_TILE{}_7 ({})".format(i,tile_indexes[288+i*2]))
        print("#define YES_TILE{}_8 ({})".format(i,tile_indexes[289+i*2]))

def get_no():
    for i in range(3,5):
        print("#define NO_TILE{}_1 ({})".format(i-3,tile_indexes[192+i*2]))
        print("#define NO_TILE{}_2 ({})".format(i-3,tile_indexes[193+i*2]))
        print("#define NO_TILE{}_3 ({})".format(i-3,tile_indexes[224+i*2]))
        print("#define NO_TILE{}_4 ({})".format(i-3,tile_indexes[225+i*2]))
        print("#define NO_TILE{}_5 ({})".format(i-3,tile_indexes[256+i*2]))
        print("#define NO_TILE{}_6 ({})".format(i-3,tile_indexes[257+i*2]))
        print("#define NO_TILE{}_7 ({})".format(i-3,tile_indexes[288+i*2]))
        print("#define NO_TILE{}_8 ({})".format(i-3,tile_indexes[289+i*2]))

def print_msg_init_data():
    print "// msg_init_data"
    x_offset = 41
    y_offset = 1
    for i in range(0,11):
        print("        {{ ({} + {}    ), ({}    ), MSG_TILE{}_1}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({}    ), MSG_TILE{}_2}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {}    ), ({} + 1), MSG_TILE{}_3}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({} + 1), MSG_TILE{}_4}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {}    ), ({} + 2), MSG_TILE{}_5}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({} + 2), MSG_TILE{}_6}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {}    ), ({} + 3), MSG_TILE{}_7}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({} + 3), MSG_TILE{}_8}},".format(x_offset,i*2,y_offset,i))

def print_yes_init_data():
    print "// yes_init_data"
    x_offset = 45
    y_offset = 7
    for i in range(0,3):
        print("        {{ ({} + {}    ), ({}    ), YES_TILE{}_1}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({}    ), YES_TILE{}_2}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {}    ), ({} + 1), YES_TILE{}_3}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({} + 1), YES_TILE{}_4}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {}    ), ({} + 2), YES_TILE{}_5}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({} + 2), YES_TILE{}_6}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {}    ), ({} + 3), YES_TILE{}_7}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({} + 3), YES_TILE{}_8}},".format(x_offset,i*2,y_offset,i))

def print_no_init_data():
    print "// no_init_data"
    x_offset = 55
    y_offset = 7
    for i in range(0,2):
        print("        {{ ({} + {}    ), ({}    ), NO_TILE{}_1}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({}    ), NO_TILE{}_2}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {}    ), ({} + 1), NO_TILE{}_3}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({} + 1), NO_TILE{}_4}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {}    ), ({} + 2), NO_TILE{}_5}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({} + 2), NO_TILE{}_6}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {}    ), ({} + 3), NO_TILE{}_7}},".format(x_offset,i*2,y_offset,i))
        print("        {{ ({} + {} + 1), ({} + 3), NO_TILE{}_8}},".format(x_offset,i*2,y_offset,i))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("USAGE: python tile_index_from_s_file.py S_FILENAME")
    else:
        #print(sys.argv[1])
        read_tile_indexes(sys.argv[1])
        get_wall_tile()
        get_message()
        get_yes()
        get_no()

        print_msg_init_data()
        print_yes_init_data()
        print_no_init_data()

