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
                
                current_control = name                              
                controls[current_form][current_control] = {}
                controls[current_form][current_control]['Type'] = control_type
                controls[current_form][current_control]['Name'] = current_control
                controls[current_form][current_control]['Number'] = extract_number_from_name(current_control)
                
            elif alias_match and current_form and current_control:
                controls[current_form][current_control]['Alias'] = alias_match.group(1)
    return controls

def generate_control_type(control_type):
    string_map = {
        "iLedDigits": "GENIE_OBJ_ILED_DIGITS",
        "StaticText": "GENIE_OBJ_STATIC_TEXT",
        "Line": "-1", # Not supported
        "Rectangle": "-1" # Not supported
    }
    return string_map.get(control_type, f"GENIE_OBJ_{control_type.upper()}")

def generate_cpp_header(controls, output_path):
    with open(output_path, 'w') as file:
        file.write(
"""// Copyright (c) 2024 James Clough (Clough42, LLC)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef HMI_CONSTANTS_H
#define HMI_CONSTANTS_H

#include <genieArduinoDEV.h>

namespace HMI {

    constexpr int UNITS_BUTTON_VAL_INCH = 0;
    constexpr int UNITS_BUTTON_VAL_MM = 1;

""")
        for form_name, form_data in controls.items():
            for control_type, control_data in form_data.items():
                control_type = control_data.get('Type')
                control_name = control_data.get('Name')
                control_alias = control_data.get('Alias')
                control_number = control_data.get('Number')
                
                if control_name and control_alias:
                    if control_type == 'Form':
                        file.write(f'\t// {control_type} {control_number}: {control_alias}\n')
                        file.write(f'\tnamespace {control_alias.upper()} {{\n\n')
                        file.write(f'\t\tconstexpr int FORM_ID = {control_number};\n\n')
                    else:
                        file.write(f'\t\t// {control_type} {control_number}: {control_alias}\n')
                        file.write(f'\t\tconstexpr int {control_alias}_TYPE = {generate_control_type(control_type)};\n')
                        file.write(f'\t\tconstexpr int {control_alias}_ID = {control_number};\n\n')
            file.write('\t}\n\n')
        file.write(
"""}

#endif // HMI_CONSTANTS_H
""")

def main():
    input_file = 'SurfaceGrinder.4DGenie'  # Path to your .4DGenie file
    output_file = '../ClearCoreArduino/HMIConstants.h'  # Path to the output C++ header file
    controls = parse_4dgenie_file(input_file)
    generate_cpp_header(controls, output_file)
    print(f'Header file {output_file} generated successfully.')

if __name__ == '__main__':
    main()