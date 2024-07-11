import sys

level_set_data = []
level_data = []
level_id = []

def file2data(filename):
    found_level_set_flg = False
    found_level_flg = False
    tmp_level = []
    tmp_index = 0
    tmp_name = []
    tmp_atom = []
    tmp_feld = []
    tmp_mole = []

    y_idx = 0
    with open(filename) as file:
        for line in file:
            if found_level_set_flg == False:
                if "[LevelSet]" in line:
                    found_level_set_flg = True
                    #print("found [LevelSet]")
            else:
                line_no_newline = line.rstrip()
                data_list = line_no_newline.split("=")
                if len(data_list) < 2:
                    #print("[LevelSet] end")
                    y_idx += 1
                    break
                else:
                    level_set_data.append(data_list)
            y_idx += 1

        for line in file:
            if "[Level" in line:
                if found_level_flg == True:
                    print("Error")
                    break
                else:
                    str_start = line.find("l") + 1
                    str_end = line.find("]")
                    tmp_index = line[str_start:str_end]
                    found_level_flg = True
            elif found_level_flg == True:
                line_no_newline = line.rstrip()
                data_list = line_no_newline.split("=")

                if len(data_list) < 2:
                    #print("[LevelNN] end")
                    tmp_level.append(tmp_index)
                    tmp_level.append(tmp_name)
                    tmp_level.append(tmp_atom)
                    tmp_level.append(tmp_feld)
                    tmp_level.append(tmp_mole)
                    level_data.append(tmp_level)
                    level_id.append(tmp_index)

                    tmp_level = []
                    tmp_index = 0
                    tmp_name = []
                    tmp_atom = []
                    tmp_feld = []
                    tmp_mole = []
                    found_level_flg = False

                    y_idx += 1
                    continue
                elif "Name" in data_list[0]:
                    tmp_name.append(data_list)
                elif "atom_" in data_list[0]:
                    tmp_atom.append(data_list)
                elif "feld_" in data_list[0]:
                    tmp_feld.append(data_list)
                elif "mole_" in data_list[0]:
                    tmp_mole.append(data_list)
            else:
                pass
            
            y_idx += 1

def level2code():
    for level in level_data:
        for name in level[1]:
            if name[0] == "Name":
                print("// Level{}: {}".format(level[0], name[1]))
                print("struct level{}_static_data {{".format(level[0]))
                print("const char* level_name=\"{}\";".format(name[1]))

        atom_index = 1
        print("unsigned short atom_list[{}][2] = {{".format(len(level[2])))
        for atom in level[2]:
            # validate index
            current_index = 0
            current_index_str = atom[0][5]
            if (ord("a") <= ord(current_index_str)) and (ord(current_index_str) <= ord("z")):
                current_index = 10 + ord(current_index_str) - ord("a")
            else:
                current_index = int(current_index_str)
            if atom_index != current_index:
                print "ERROR: invalid atom index:", current_index 

            atom_id = 0
            atom_val = atom[1].split("-")
            if (ord("A") <= ord(atom_val[0])) and (ord(atom_val[0]) <= ord("D")):
                atom_id = 0x0100 + 10 + ord(atom_val[0]) - ord("A")
            elif "o" == atom_val[0]:
                # Crystal
                atom_id = 10 + ord(atom_val[0]) - ord("a")
            else:
                atom_id = int(atom_val[0])

            atom_conn_flg = 0x0000
            ascii_diff = 0
            for conn_id in atom_val[1]:
                if (ord("a") <= ord(conn_id)) and (ord(conn_id) <= ord("h")):
                    ascii_diff = ord(conn_id) - ord("a")
                elif (ord("A") <= ord(conn_id)) and (ord(conn_id) <= ord("H")):
                    ascii_diff = 8 + ord(conn_id) - ord("A")
                else:
                    print "ERROR: invalid atom_conn_id: ", conn_id
                atom_conn_flg |= (0x0001 << ascii_diff)

            print("{{ {}, 0x{:04X} }},".format(atom_id,atom_conn_flg))
            atom_index += 1
        print ("};")

        sharp_count = 0
        print ("char feld_map[15][15] = {")
        for feld in level[3]:
            print "{",
            for c in feld[1]:
                hex_val = 0
                if c == ".":
                    hex_val = -1 & (2**8-1)
                    print("0x{:02X},".format(hex_val)),
                elif c == "#":
                    sharp_count += 1
                    hex_val = -2 & (2**8-1)
                    print("0x{:02X},".format(hex_val)),
                elif (ord("a") <= ord(c)) and (ord(c) <= ord("z")):
                    ascii_diff_val = ord(c) - ord("a")
                    feld_val = 10 + ascii_diff_val
                    print feld_val,",",
                else:
                    print c,",",
            print("},")
        print ("};")
        print("// #sharp_count={}".format(sharp_count))

        max_length = 0
        for mole in level[4]:
            if len(mole[1]) > max_length:
                max_length = len(mole[1])

        print("char mole[{}][{}] = {{".format(len(level[4]), max_length+1))
        for mole in level[4]:
            print "{",
            hex_val = 0
            mole_index = 0
            for c in mole[1]:
                if c == ".":
                    hex_val = -1 & (2**8-1)
                    print("0x{:02X},".format(hex_val)),
                    #print "-1,",
                elif (ord('a') <= ord(c)) and (ord(c) <= ord('z')):
                    ascii_diff_val = ord(c) - ord('a')
                    mole_val = 10 + ascii_diff_val
                    print mole_val,",",
                else:
                    print c,",",
                mole_index += 1

            # fill tail
            while (mole_index < max_length):
                hex_val = -1 & (2**8-1)
                print("0x{:02X},".format(hex_val)),
                mole_index += 1
            
            # print terminator
            print "0, },"
        print ("};")

        print ("};")
        print("BN_DATA_EWRAM level{}_static_data level{}_data;".format(level[0],level[0]))
        print("")

def output_all_list():
    all_list_id = []
    all_list_id = sorted(level_id, key=lambda num_str: int(num_str))
    all_list_size = len(all_list_id)

    print "// all list"
    print "#include \"ag_array_t.h\""
    print "struct all_level_static_data {"

    #name
    print("const char* name_list[{}] = {{".format(all_list_size))
    for index in all_list_id:
        print("level{}_data.level_name,".format(index))
    print "};"

    #atom
    print("struct ag::array_t<unsigned short*> atom_list[{}] = {{".format(all_list_size))
    for index in all_list_id:
        print("{{ sizeof(level{}_data.atom_list)/sizeof(level{}_data.atom_list[0]), (unsigned short**)level{}_data.atom_list }},".format(index,index,index))
    print "};"

    #feld
    print("struct ag::array_t<char*> feld_list[{}] = {{".format(all_list_size))
    for index in all_list_id:
        print("{{ sizeof(level{}_data.feld_map)/sizeof(level{}_data.feld_map[0]), (char**)level{}_data.feld_map }},".format(index,index,index))
    print "};"

    #mole
    print("struct ag::array_t<char*> mole_list[{}] = {{".format(all_list_size))
    for index in all_list_id:
        print("{{ sizeof(level{}_data.mole)/sizeof(level{}_data.mole[0]), (char**)level{}_data.mole }},".format(index,index,index))
    print "};"

    print "};"
    print "BN_DATA_EWRAM all_level_static_data all_level_data;"

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("USAGE: python level2init_data.py FILENAME")
    else:
        #print(sys.argv[1])
        file2data(sys.argv[1])
        print("// level_data_num = {}".format(len(level_data)))
        
        if len(level_data) > 0:
            print("namespace ag {")
            level2code()
            output_all_list()
            print("}")
