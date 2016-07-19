#ifndef	READ_BLIF_H
#define READ_BLIF_H

void read_and_process_blif(char *blif_file,
		bool sweep_hanging_nets_and_inputs, bool absorb_buffer_luts,           
        t_model *user_models,
		t_model *library_models, bool read_activity_file,
		char * activity_file);
void echo_input(char *blif_file, char *echo_file, t_model *library_models);
void dum_parse(char *buf);

#endif /*READ_BLIF_H*/
