# This file is automatically generated.
# It contains project source information necessary for synthesis and implementation.

# XDC: /home/INTRA/esmost/workspace/project/audioip_lab4/zedboard_audio/constraints/zed_audio.xdc

# Block Designs: bd/Audio/Audio.bd
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio || ORIG_REF_NAME==Audio}]

# IP: bd/Audio/ip/Audio_processing_system7_0_0/Audio_processing_system7_0_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_processing_system7_0_0 || ORIG_REF_NAME==Audio_processing_system7_0_0}]

# IP: bd/Audio/ip/Audio_processing_system7_0_axi_periph_0/Audio_processing_system7_0_axi_periph_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_processing_system7_0_axi_periph_0 || ORIG_REF_NAME==Audio_processing_system7_0_axi_periph_0}]

# IP: bd/Audio/ip/Audio_rst_processing_system7_0_100M_0/Audio_rst_processing_system7_0_100M_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_rst_processing_system7_0_100M_0 || ORIG_REF_NAME==Audio_rst_processing_system7_0_100M_0}]

# IP: bd/Audio/ip/Audio_myip_0_4/Audio_myip_0_4.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_myip_0_4 || ORIG_REF_NAME==Audio_myip_0_4}]

# IP: bd/Audio/ip/Audio_audio_zed_0_0/Audio_audio_zed_0_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_audio_zed_0_0 || ORIG_REF_NAME==Audio_audio_zed_0_0}]

# IP: bd/Audio/ip/Audio_xlconstant_0_0/Audio_xlconstant_0_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_xlconstant_0_0 || ORIG_REF_NAME==Audio_xlconstant_0_0}]

# IP: bd/Audio/ip/Audio_mixer_0_0/Audio_mixer_0_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_mixer_0_0 || ORIG_REF_NAME==Audio_mixer_0_0}]

# IP: bd/Audio/ip/Audio_FILTER_IIR_0_0/Audio_FILTER_IIR_0_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_FILTER_IIR_0_0 || ORIG_REF_NAME==Audio_FILTER_IIR_0_0}]

# IP: bd/Audio/ip/Audio_xbar_0/Audio_xbar_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_xbar_0 || ORIG_REF_NAME==Audio_xbar_0}]

# IP: bd/Audio/ip/Audio_Volume_Pregain_0_0/Audio_Volume_Pregain_0_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_Volume_Pregain_0_0 || ORIG_REF_NAME==Audio_Volume_Pregain_0_0}]

# IP: bd/Audio/ip/Audio_FILTER_IIR_1_0/Audio_FILTER_IIR_1_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_FILTER_IIR_1_0 || ORIG_REF_NAME==Audio_FILTER_IIR_1_0}]

# IP: bd/Audio/ip/Audio_Volume_Pregain_1_0/Audio_Volume_Pregain_1_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_Volume_Pregain_1_0 || ORIG_REF_NAME==Audio_Volume_Pregain_1_0}]

# IP: bd/Audio/ip/Audio_auto_pc_0/Audio_auto_pc_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==Audio_auto_pc_0 || ORIG_REF_NAME==Audio_auto_pc_0}]

# XDC: bd/Audio/ip/Audio_processing_system7_0_0/Audio_processing_system7_0_0.xdc
set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==Audio_processing_system7_0_0 || ORIG_REF_NAME==Audio_processing_system7_0_0}] {/inst }]/inst ]]

# XDC: bd/Audio/ip/Audio_rst_processing_system7_0_100M_0/Audio_rst_processing_system7_0_100M_0_board.xdc
set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==Audio_rst_processing_system7_0_100M_0 || ORIG_REF_NAME==Audio_rst_processing_system7_0_100M_0}] {/U0 }]/U0 ]]

# XDC: bd/Audio/ip/Audio_rst_processing_system7_0_100M_0/Audio_rst_processing_system7_0_100M_0.xdc
#dup# set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==Audio_rst_processing_system7_0_100M_0 || ORIG_REF_NAME==Audio_rst_processing_system7_0_100M_0}] {/U0 }]/U0 ]]

# XDC: bd/Audio/ip/Audio_rst_processing_system7_0_100M_0/Audio_rst_processing_system7_0_100M_0_ooc.xdc

# XDC: bd/Audio/ip/Audio_xbar_0/Audio_xbar_0_ooc.xdc

# XDC: bd/Audio/ip/Audio_auto_pc_0/Audio_auto_pc_0_ooc.xdc

# XDC: bd/Audio/Audio_ooc.xdc
