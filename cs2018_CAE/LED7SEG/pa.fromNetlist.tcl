
# PlanAhead Launch Script for Post-Synthesis pin planning, created by Project Navigator

create_project -name LED7SEG -dir "/home/ise/cs2018_CAE/LED7SEG/planAhead_run_1" -part xc6slx4tqg144-3
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "/home/ise/cs2018_CAE/LED7SEG/led7seg.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {/home/ise/cs2018_CAE/LED7SEG} }
set_param project.pinAheadLayout  yes
set_property target_constrs_file "led7seg.ucf" [current_fileset -constrset]
add_files [list {led7seg.ucf}] -fileset [get_property constrset [current_run]]
link_design
