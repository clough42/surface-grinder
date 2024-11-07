import re

def extract_number_from_name(name):
    match = re.search(r'\d+$', name)
    return match.group() if match else None
    
def parse_4dgenie_file(file_path):
    controls = {}
    with open(file_path, 'r') as file:
        current_form = None
        control_type = None
        current_control = None
        for line in file:
            type_match = re.match(r'^\s*(\w+)\s*$', line)
            name_match = re.match(r'^\s*Name\s+(\w+)$', line)
            alias_match = re.match(r'^\s*Alias\s+(\w+)$', line)
            
            if type_match:
                control_type = type_match.group(1)
            elif name_match and control_type:
                name = name_match.group(1)
                
                if control_type == 'Form':
                    current_form = name;
                    controls[current_form] = {}
                    current_control = None
                
                else:
                    current_control = name                              
                    controls[current_form][current_control] = {}
                    controls[current_form][current_control]['Type'] = control_type
                    controls[current_form][current_control]['Name'] = current_control
                    controls[current_form][current_control]['Number'] = extract_number_from_name(current_control)
                
            elif alias_match and current_form and current_control:
                controls[current_form][current_control]['Alias'] = alias_match.group(1)
    return controls

def generate_cpp_header(controls, output_path):
    with open(output_path, 'w') as file:
        file.write('#ifndef HMI_CONSTANTS_H\n')
        file.write('#define HMI_CONSTANTS_H\n\n')
        file.write('namespace HMI {\n\n')
        for form_name, form_data in controls.items():
            file.write(f'\tnamespace {form_name} {{\n\n')
            for control_type, control_data in form_data.items():
                control_type = control_data.get('Type')
                control_name = control_data.get('Name')
                control_alias = control_data.get('Alias')
                control_number = control_data.get('Number')
                if control_name and control_alias:
                    file.write(f'\t\t// {control_type} {control_number}: {control_alias}\n')
                    file.write(f'\t\tconstexpr int {control_alias}_TYPE = GENIE_OBJ_{control_type.upper()};\n')
                    file.write(f'\t\tconstexpr int {control_alias}_ID = {control_number};\n\n')
            file.write('\t}\n\n')
        file.write('}\n')
        file.write('#endif // HMI_CONSTANTS_H\n')

def main():
    input_file = 'SurfaceGrinder.4DGenie'  # Path to your .4DGenie file
    output_file = 'HMIConstants.h'  # Path to the output C++ header file
    controls = parse_4dgenie_file(input_file)
    generate_cpp_header(controls, output_file)
    print(f'Header file {output_file} generated successfully.')

if __name__ == '__main__':
    main()