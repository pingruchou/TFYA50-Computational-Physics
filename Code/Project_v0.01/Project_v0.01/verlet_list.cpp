#include "verlet_list.h"

#define cutoff 500

verlet_list::verlet_list()
{
	data = 0;
	next = 0;
}

/* This function needs to be changed */
/* Currently it does not care about periodic boundary conditions */
float distance(vector_3d a, vector_3d b)
{
	vector_3d res = a-b;
	return res.abs();
}

/* This function needs the proper cutoff distance, somehow, perhaps as a private member or something? */
void verlet_list::add_atom(verlet_list atom)
{
	verlet_list *next_atom = this->next;
	if(distance(this->data->pos, atom.data->pos) < cutoff){
		this->next = new verlet_list();
		this->next->data = atom.data;
		this->next->next = next_atom;
	}
}

/* This seems to work, should limit our potential memory leaks at least */
void verlet_list::clear_verlet_list()
{
	verlet_list *current = this->next;
	verlet_list *previous = 0;

	while(current != 0){
		previous = current;
		current = current->next;
		delete previous;
	}

	this->next = 0;
}