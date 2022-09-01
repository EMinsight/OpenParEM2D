////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    OpenParEM2D - A fullwave 2D electromagnetic simulator.                  //
//    Copyright (C) 2022 Brian Young                                          //
//                                                                            //
//    This program is free software: you can redistribute it and/or modify    //
//    it under the terms of the GNU General Public License as published by    //
//    the Free Software Foundation, either version 3 of the License, or       //
//    (at your option) any later version.                                     //
//                                                                            //
//    This program is distributed in the hope that it will be useful,         //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of          //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           //
//    GNU General Public License for more details.                            //
//                                                                            //
//    You should have received a copy of the GNU General Public License       //
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// C version of the setup information data.
// Do this in C so that it can be passed to eigensolve.c

#include "project.h"

// allocate memory and copy a string
char* allocCopyString (char *a) {
   char *b=NULL;

   if (a == NULL) return NULL;

   b=(char *)malloc((strlen(a)+1)*sizeof(char));
   if (b == NULL) return NULL;
   strcpy(b,a);

   return b;
}

char* removeNewLineChar (char *a) {
   int i;

   if (a == NULL) return NULL;

   i=0;
   while (i < strlen(a)) {
      if (a[i] == '\n') {a[i]='\0'; break;}
      i++;
   }

   return a;
}

char *removeComment (char *a) {
   long int i;

   if (a == NULL) return NULL;

   // remove comment 
   i=0;
   while (i < strlen(a)-1) {
      if (a[i] == '/' && a[i+1] == '/') {a[i]='\0'; break;}
      i++;
   }

   // remove trailing spaces
   i=strlen(a)-1;
   while (i >= 0) {
      if (a[i] != ' ' && a[i] != '\t') {a[i+1]='\0'; break;}
      i--;
   }

   return a;
}

int removeQuote (char *a) {
   int i,j,len;

   if (a == NULL) return 0;

   len=strlen(a);
   i=0;
   while (i < len) {
      if (a[i] == '"') {
         j=i;
         while (j < len) {
            a[j]=a[j+1];
            j++;
         }
         return 1;
      }
      i++;
   }

   return 0;
}

void removeQuotes (char *a) {
   while (removeQuote(a));
}

int removeSpace (char *a) {
   int i,j,len;

   if (a == NULL) return 0;

   len=strlen(a);
   i=0;
   while (i < len) {
      if (a[i] == ' ' || a[i] == '\t') {
         j=i;
         while (j < len) {
            a[j]=a[j+1];
            j++;
         }
         return 1;
      }
      i++;
   }

   return 0;
}

void removeSpaces (char *a) {
   while (removeSpace(a));
}

int is_blank (char *a) {
   int i=0;
   while (i < strlen(a)) {
      if (a[i] != ' ' && a[i] != '\n' && a[i] != '\t') return 0;
      i++;
   }
   return 1;
}

int is_text (char *a) {
   if (a == NULL) return 0;
   if (strlen(a) == 0) return 0;
   return 1;
}

int is_true (char *a) {
   if (a == NULL) return 0;
   if (strcmp(a,"true") == 0) return 1;
   if (strcmp(a,"TRUE") == 0) return 1;
   if (strcmp(a,"1") == 0) return 1;
   if (strcmp(a,"True") == 0) return 1;
   return 0;
}

int is_false (char *a) {
   if (a == NULL) return 0;
   if (strcmp(a,"false") == 0) return 1;
   if (strcmp(a,"FALSE") == 0) return 1;
   if (strcmp(a,"0") == 0) return 1;
   if (strcmp(a,"False") == 0) return 1;
   return 0;
}

int is_bool (char *a) {
   if (is_true(a)) return 1;
   if (is_false(a)) return 1;
   return 0;
}

int is_int (char *a) {
   int found;

   if (a == NULL) return 0;
   if (strlen(a) == 0) return 0;

   // skip leading white space
   int i=0;
   while (i < strlen(a)) {
      if (a[i] != ' ' && a[i] != '\t') break;
      i++;
   }

   // skip a leading sign
   if (i < strlen(a) && (a[i] == '-' || a[i] == '+')) i++;

   while (i < strlen(a)) {
      found=0;

      if (a[i] == '0' ||
          a[i] == '1' ||
          a[i] == '2' ||
          a[i] == '3' ||
          a[i] == '4' ||
          a[i] == '5' ||
          a[i] == '6' ||
          a[i] == '7' ||
          a[i] == '8' ||
          a[i] == '9') found=1;

      if (!found) return 0;
      
      i++;
   }
   return 1;
}

int is_double (char *a) {
   int found;
   int found_e=-1;
   int found_period=-1;
   int found_sign=-1;

   if (a == NULL) return 0;
   if (strlen(a) == 0) return 0;

   // skip leading white space
   int i=0;
   while (i < strlen(a)) {
      if (a[i] != ' ' && a[i] != '\t') break;
      i++;
   }

   // skip a leading sign
   if (i < strlen(a) && (a[i] == '-' || a[i] == '+')) i++;

   while (i < strlen(a)) {
      found=0;
      if (a[i] == '0' ||
          a[i] == '1' ||
          a[i] == '2' ||
          a[i] == '3' ||
          a[i] == '4' ||
          a[i] == '5' ||
          a[i] == '6' ||
          a[i] == '7' ||
          a[i] == '8' ||
          a[i] == '9') found=1;

      if (a[i] == 'e' || a[i] == 'E') {
         if (found_e >= 0) return 0;
         found_e=i;
         found=1;
      }

      if (a[i] == '-' || a[i] == '+') {
         if (found_sign >= 0) return 0;
         found_sign=i;
         found=1;
      }

      if (a[i] == '.') {
         if (found_period >= 0) return 0;
         found_period=i;
         found=1;
      }

      if (!found) return 0;

      i++;
   }

   if (found_period >= 0 && found_e >= 0 && found_period > found_e) return 0;
   if (found_sign >= 0) {
      if (found_e >= 0) {
         if (found_sign != found_e+1) return 0;
      } else return 0;
   }
   if (found_sign == strlen(a)-1) return 0;
   if (found_e == strlen(a)-1) return 0;

   return 1;
}

int double_compare (double a, double b, double tol)
{
   if (a == b) return 1;
   if (a == 0 && fabs(b) < tol) return 1;
   if (b == 0 && fabs(a) < tol) return 1;
   if (fabs((a-b)/a) < tol) return 1;
   return 0;
}

int is_none_impedance (char *a) {
   if (a == NULL) return 0;
   if (strcmp(a,"none") == 0) return 1;
   return 0;
}

int is_impedance (char *a) {
   if (a == NULL) return 0;
   if (strcmp(a,"PV") == 0) return 1;
   if (strcmp(a,"PI") == 0) return 1;
   if (strcmp(a,"VI") == 0) return 1;
   if (strcmp(a,"none") == 0) return 1;
   return 0;
}

int is_modal_impedance (char *a) {
   if (a == NULL) return 0;
   if (strcmp(a,"modal") == 0) return 1;
   return 0;
}

int is_line_impedance (char *a) {
   if (a == NULL) return 0;
   if (strcmp(a,"line") == 0) return 1;
   return 0;
}

int is_impedance_calculation (char *a) {
   if (is_modal_impedance(a) || is_line_impedance(a)) return 1;
   return 0;
}

int is_refinement_frequency (char *a) {
   if (a == NULL) return 0;
   if (strcmp(a,"all") == 0) return 1;
   if (strcmp(a,"none") == 0) return 1;
   if (strcmp(a,"high") == 0) return 1;
   if (strcmp(a,"low") == 0) return 1;
   if (strcmp(a,"highlow") == 0) return 1;
   if (strcmp(a,"lowhigh") == 0) return 1;
   if (strcmp(a,"plan") == 0) return 1;
   return 0;
}


// not zero based for mode
int get_refinement_variable (char *refinement_variable, int mode)
{
   char *test=NULL,*keyword=NULL;
   int i,last_mode;

   if (refinement_variable == NULL) return 0;
   if (is_blank(refinement_variable)) return 0;

   test=allocCopyString(refinement_variable);
   if (test == NULL) return 0;

   test=removeNewLineChar(test);
   test=removeComment(test);
   removeSpaces(test);

   last_mode=0;

   i=1;
   while (i <= mode) {
      if (i == 1) keyword=strtok(test,",");
      else keyword=strtok(NULL,",");

      if (keyword == NULL) break;
      else {
         if (strcmp(keyword,"none") == 0) last_mode=NONE;
         else if (strcmp(keyword,"alpha") == 0) last_mode=ALPHA;
         else if (strcmp(keyword,"beta") == 0) last_mode=BETA;
         else if (strcmp(keyword,"|gamma|") == 0) last_mode=ABSGAMMA;
         else if (strcmp(keyword,"|Zo|") == 0) last_mode=ABSZO;
         else if (strcmp(keyword,"Re(Zo)") == 0) last_mode=REZO;
         else if (strcmp(keyword,"Im(Zo)") == 0) last_mode=IMZO;
         else {last_mode=0; break;}
      }
      i++;
   }

   if (test != NULL) {free(test); test=NULL;}
   return last_mode;
}

int is_impedance_refinement_variable (char *refinement_variable, int mode)
{
   if (get_refinement_variable(refinement_variable,mode) == ABSZO) return 1;
   if (get_refinement_variable(refinement_variable,mode) == REZO) return 1;
   if (get_refinement_variable(refinement_variable,mode) == IMZO) return 1;
   return 0;
}

// not zero based for mode
double get_refinement_tolerance (char *refinement_tolerance, int mode)
{
   char *test=NULL,*keyword=NULL;
   int i;
   double last_mode;

   if (refinement_tolerance == NULL) return 0;
   if (is_blank(refinement_tolerance)) return 0;

   test=allocCopyString(refinement_tolerance);
   if (test == NULL) return 0;

   test=removeNewLineChar(test);
   test=removeComment(test);
   removeSpaces(test);

   last_mode=0;

   i=1;
   while (i <= mode) {
      if (i == 1) keyword=strtok(test,",");
      else keyword=strtok(NULL,",");

      if (keyword == NULL) break;
      else last_mode=atof(keyword);
      i++;
   }

   if (test != NULL) {free(test); test=NULL;}
   return last_mode;
}

void add_inputFrequencyPlan (struct projectData *data, int type, double frequency, double start, double stop, double step, int pointsPerDecade, int lineNumber, int refine)
{
   // allocate more plans, if needed
   if (data->inputFrequencyPlansCount == data->inputFrequencyPlansAllocated) {
      data->inputFrequencyPlansAllocated+=5;
      data->inputFrequencyPlans=(struct inputFrequencyPlan *) realloc (data->inputFrequencyPlans,data->inputFrequencyPlansAllocated*sizeof(struct inputFrequencyPlan));
   }

   // assign the next plan and update the counter
   if (type == 0) {
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].type=type;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].frequency=-1;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].start=start;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].stop=stop;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].step=step;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].pointsPerDecade=-1;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].lineNumber=lineNumber;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].refine=refine;
   } else if (type == 1) {
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].type=type;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].frequency=-1;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].start=start;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].stop=stop;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].step=-1;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].pointsPerDecade=pointsPerDecade;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].lineNumber=lineNumber;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].refine=refine;
   } else if (type == 2) {
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].type=type;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].frequency=frequency;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].start=-1;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].stop=-1;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].step=-1;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].pointsPerDecade=-1;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].lineNumber=lineNumber;
      data->inputFrequencyPlans[data->inputFrequencyPlansCount].refine=refine;
   }
   data->inputFrequencyPlansCount++;
}

void init_project (struct projectData *data) {

   data->version_name=allocCopyString("#OpenParEM2Dproject");
   data->version_value=allocCopyString("1.0");

   data->project_name=allocCopyString("");
   data->project_save_fields=0;

   data->mesh_file=allocCopyString("");
   data->mesh_order=1;
   data->mesh_uniform_refinement_count=0;
   data->mesh_refinement_cutoff=0.7;
   data->mesh_refinement_fraction=0.025;

   data->mode_definition_file=allocCopyString("");

   data->refinement_frequency=allocCopyString("highlow");
   data->refinement_variable=allocCopyString("|Zo|");
   data->refinement_iteration_min=1;
   data->refinement_iteration_max=10;
   data->refinement_required_passes=3;
   data->refinement_tolerance=allocCopyString("1e-3");
   data->refinement_refine_converged_modes=1;

   data->materials_global_path=allocCopyString("../");
   data->materials_global_name=allocCopyString("global_materials");
   data->materials_local_path=allocCopyString("./");
   data->materials_local_name=allocCopyString("local_materials");
   data->materials_check_limits=1;

   data->inputFrequencyPlansAllocated=5;
   data->inputFrequencyPlansCount=0;
   data->inputFrequencyPlans=(struct inputFrequencyPlan *)malloc(data->inputFrequencyPlansAllocated*sizeof(struct inputFrequencyPlan));

   data->solution_modes=1;
   data->solution_temperature=25; 
   data->solution_tolerance=1e-13;
   data->solution_iteration_limit=5000;
   data->solution_modes_buffer=5;
   data->solution_impedance_definition=allocCopyString("none");
   data->solution_impedance_calculation=allocCopyString("modal");
   data->solution_check_closed_loop=0;
   data->solution_accurate_residual=0;
   data->solution_shift_invert=1;
   data->solution_use_initial_guess=1;
   data->solution_shift_factor=1;

   data->output_show_refining_mesh=0;
   data->output_show_postprocessing=0;
   data->output_show_iterations=0;
   data->output_show_license=0;

   data->test_create_cases=0;
   data->test_show_audit=0;
   data->test_show_detailed_cases=0;

   data->debug_show_memory=0;
   data->debug_show_project=0;
   data->debug_show_frequency_plan=0;
   data->debug_show_materials=0;
   data->debug_show_mode_definitions=0;
   data->debug_show_impedance_details=0;
   data->debug_skip_solve=0;
   data->debug_tempfiles_keep=0;

   data->solution_active_mode_count=-1;
   data->field_points_count=-1;
   data->field_points_allocated=0;
   data->field_points_x=NULL;
   data->field_points_y=NULL;
}

void free_project (struct projectData *data) {
   if (data == NULL) return;

   if (data->version_name) free (data->version_name);
   if (data->version_value) free (data->version_value);
   if (data->project_name) free (data->project_name);
   if (data->mesh_file) free (data->mesh_file);
   if (data->mode_definition_file) free (data->mode_definition_file);
   if (data->materials_global_path) free (data->materials_global_path);
   if (data->materials_global_name) free (data->materials_global_name);
   if (data->materials_local_path) free (data->materials_local_path);
   if (data->materials_local_name) free (data->materials_local_name);
   if (data->refinement_variable) free (data->refinement_variable);
   if (data->refinement_tolerance) free (data->refinement_tolerance);
   if (data->solution_impedance_definition) free (data->solution_impedance_definition);
   if (data->solution_impedance_calculation) free (data->solution_impedance_calculation);
   if (data->inputFrequencyPlans) free(data->inputFrequencyPlans);
   if (data->field_points_x) free(data->field_points_x);
   if (data->field_points_y) free(data->field_points_y);
}

void print_project (struct projectData *data, struct projectData *defaultData, const char *indent) {
   int i;
   int matched=0;
   char* logic[2];
   char* comment[2];

   if (data == NULL) return;


   logic[0]=allocCopyString("false");
   logic[1]=allocCopyString("true");

   comment[0]=allocCopyString("");
   comment[1]=allocCopyString("//");

   PetscPrintf(PETSC_COMM_WORLD,"%s%s %s\n",indent,data->version_name,data->version_value);
   PetscPrintf(PETSC_COMM_WORLD,"%s//Commented lines show either unspecified inputs that utilize the default values or specified inputs that match the default values.\n",indent);

   matched=0;  if (defaultData && data->project_save_fields == defaultData->project_save_fields) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%sproject.save.fields %s\n",indent,comment[matched],logic[data->project_save_fields]);

   matched=0; if (defaultData && strcmp(data->mesh_file,defaultData->mesh_file) == 0) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%smesh.file %s\n",indent,comment[matched],data->mesh_file);

   matched=0; if (defaultData && data->mesh_order == defaultData->mesh_order) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%smesh.order %d\n",indent,comment[matched],data->mesh_order);

   matched=0; if (defaultData && data->mesh_uniform_refinement_count == defaultData->mesh_uniform_refinement_count) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%smesh.uniform_refinement.count %d\n",indent,comment[matched],data->mesh_uniform_refinement_count);

   matched=0; if (defaultData && double_compare(data->mesh_refinement_cutoff,defaultData->mesh_refinement_cutoff,1e-14)) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%smesh.refinement.cutoff %g\n",indent,comment[matched],data->mesh_refinement_cutoff);

   matched=0; if (defaultData && double_compare(data->mesh_refinement_fraction,defaultData->mesh_refinement_fraction,1e-14)) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%smesh.refinement.fraction %g\n",indent,comment[matched],data->mesh_refinement_fraction);

   matched=0; if (defaultData && strcmp(data->mode_definition_file,defaultData->mode_definition_file) == 0) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%smode.definition.file %s\n",indent,comment[matched],data->mode_definition_file);

   matched=0; if (defaultData && strcmp(data->refinement_frequency,defaultData->refinement_frequency) == 0) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%srefinement.frequency %s\n",indent,comment[matched],data->refinement_frequency);

   matched=0; if (defaultData && strcmp(data->refinement_variable,defaultData->refinement_variable) == 0) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%srefinement.variable %s\n",indent,comment[matched],data->refinement_variable);

   matched=0; if (defaultData && data->refinement_iteration_min == defaultData->refinement_iteration_min) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%srefinement.iteration.min %d\n",indent,comment[matched],data->refinement_iteration_min);

   matched=0; if (defaultData && data->refinement_iteration_max == defaultData->refinement_iteration_max) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%srefinement.iteration.max %d\n",indent,comment[matched],data->refinement_iteration_max);

   matched=0; if (defaultData && data->refinement_required_passes == defaultData->refinement_required_passes) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%srefinement.required.passes %d\n",indent,comment[matched],data->refinement_required_passes);

   matched=0; if (defaultData && strcmp(data->refinement_tolerance,defaultData->refinement_tolerance) == 0) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%srefinement.tolerance %s\n",indent,comment[matched],data->refinement_tolerance);

   matched=0; if (defaultData && strcmp(data->materials_global_path,defaultData->materials_global_path) == 0) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%smaterials.global.path %s\n",indent,data->materials_global_path);

   matched=0; if (defaultData && strcmp(data->materials_global_name,defaultData->materials_global_name) == 0) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%smaterials.global.name %s\n",indent,data->materials_global_name);

   matched=0; if (defaultData && strcmp(data->materials_local_path,defaultData->materials_local_path) == 0) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%smaterials.local.path %s\n",indent,data->materials_local_path);

   matched=0; if (defaultData && strcmp(data->materials_local_name,defaultData->materials_local_name) == 0) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%smaterials.local.name %s\n",indent,data->materials_local_name);

   matched=0;  if (defaultData && data->materials_check_limits == defaultData->materials_check_limits) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%smaterials.check.limits %s\n",indent,comment[matched],logic[data->materials_check_limits]);

   // no default frequency plans, so print all
   i=0;
   while (i < data->inputFrequencyPlansCount) {
      if (data->inputFrequencyPlans[i].type == 0) {
         if (data->inputFrequencyPlans[i].refine == 0) {
            PetscPrintf(PETSC_COMM_WORLD,"%sfrequency.plan.linear %g,%g,%g\n",indent,
                        data->inputFrequencyPlans[i].start,data->inputFrequencyPlans[i].stop,data->inputFrequencyPlans[i].step);
         } else {
            PetscPrintf(PETSC_COMM_WORLD,"%sfrequency.plan.linear.refine %g,%g,%g\n",indent,
                        data->inputFrequencyPlans[i].start,data->inputFrequencyPlans[i].stop,data->inputFrequencyPlans[i].step);
         }
      } else if (data->inputFrequencyPlans[i].type == 1) {
         if (data->inputFrequencyPlans[i].refine == 0) {
            PetscPrintf(PETSC_COMM_WORLD,"%sfrequency.plan.log %g,%g,%d\n",indent,
                        data->inputFrequencyPlans[i].start,data->inputFrequencyPlans[i].stop,data->inputFrequencyPlans[i].pointsPerDecade);
         } else {
            PetscPrintf(PETSC_COMM_WORLD,"%sfrequency.plan.log.refine %g,%g,%d\n",indent,
                        data->inputFrequencyPlans[i].start,data->inputFrequencyPlans[i].stop,data->inputFrequencyPlans[i].pointsPerDecade);
         }
      } else if (data->inputFrequencyPlans[i].type == 2) {
         if (data->inputFrequencyPlans[i].refine == 0) {
            PetscPrintf(PETSC_COMM_WORLD,"%sfrequency.plan.point %g\n",indent,data->inputFrequencyPlans[i].frequency);
         } else {
            PetscPrintf(PETSC_COMM_WORLD,"%sfrequency.plan.point.refine %g\n",indent,data->inputFrequencyPlans[i].frequency);
         }
      }
      i++;
   }

   matched=0; if (defaultData && data->solution_modes == defaultData->solution_modes) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%ssolution.modes %d\n",indent,comment[matched],data->solution_modes);

   matched=0; if (defaultData && double_compare(data->solution_temperature,defaultData->solution_temperature,1e-14)) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%ssolution.temperature %g\n",indent,comment[matched],data->solution_temperature);

   matched=0; if (defaultData && double_compare(data->solution_tolerance,defaultData->solution_tolerance,1e-14)) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%ssolution.tolerance %g\n",indent,comment[matched],data->solution_tolerance);

   matched=0; if (defaultData && data->solution_iteration_limit == defaultData->solution_iteration_limit) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%ssolution.iteration.limit %d\n",indent,comment[matched],data->solution_iteration_limit);

   matched=0; if (defaultData && data->solution_modes_buffer == defaultData->solution_modes_buffer) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%ssolution.modes.buffer %d\n",indent,comment[matched],data->solution_modes_buffer);

   matched=0; if (defaultData && strcmp(data->solution_impedance_definition,defaultData->solution_impedance_definition) == 0) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%ssolution.impedance.definition %s\n",indent,comment[matched],data->solution_impedance_definition);

   matched=0; if (defaultData && strcmp(data->solution_impedance_calculation,defaultData->solution_impedance_calculation) == 0) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%ssolution.impedance.calculation %s\n",indent,comment[matched],data->solution_impedance_calculation);

   matched=0;  if (defaultData && data->solution_check_closed_loop == defaultData->solution_check_closed_loop) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%ssolution.check.closed.loop %s\n",indent,comment[matched],logic[data->solution_check_closed_loop]);

   matched=0;  if (defaultData && data->solution_accurate_residual == defaultData->solution_accurate_residual) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%ssolution.accurate.residual %s\n",indent,comment[matched],logic[data->solution_accurate_residual]);

   matched=0;  if (defaultData && data->solution_shift_invert == defaultData->solution_shift_invert) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%ssolution.shift.invert %s\n",indent,comment[matched],logic[data->solution_shift_invert]);

   matched=0;  if (defaultData && data->solution_use_initial_guess == defaultData->solution_use_initial_guess) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%ssolution.use.initial.guess %s\n",indent,comment[matched],logic[data->solution_use_initial_guess]);

   matched=0; if (defaultData && double_compare(data->solution_shift_factor,defaultData->solution_shift_factor,1e-14)) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%ssolution.shift.factor %g\n",indent,comment[matched],data->solution_shift_factor);

   matched=0;  if (defaultData && data->output_show_refining_mesh == defaultData->output_show_refining_mesh) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%soutput.show.refining.mesh %s\n",indent,comment[matched],logic[data->output_show_refining_mesh]);

   matched=0;  if (defaultData && data->output_show_postprocessing == defaultData->output_show_postprocessing) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%soutput.show.postprocessing %s\n",indent,comment[matched],logic[data->output_show_postprocessing]);

   matched=0;  if (defaultData && data->output_show_iterations == defaultData->output_show_iterations) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%soutput.show.iterations %s\n",indent,comment[matched],logic[data->output_show_iterations]);

   matched=0;  if (defaultData && data->output_show_license == defaultData->output_show_license) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%soutput.show.license %s\n",indent,comment[matched],logic[data->output_show_license]);

   matched=0;  if (defaultData && data->test_create_cases == defaultData->test_create_cases) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%stest.create.cases %s\n",indent,comment[matched],logic[data->test_create_cases]);

   matched=0;  if (defaultData && data->test_show_audit == defaultData->test_show_audit) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%stest.show.audit %s\n",indent,comment[matched],logic[data->test_show_audit]);

   matched=0;  if (defaultData && data->test_show_detailed_cases == defaultData->test_show_detailed_cases) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%stest.show.detailed.cases %s\n",indent,comment[matched],logic[data->test_show_detailed_cases]);

   matched=0;  if (defaultData && data->debug_show_memory == defaultData->debug_show_memory) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%sdebug.show.memory %s\n",indent,comment[matched],logic[data->debug_show_memory]);

   matched=0;  if (defaultData && data->debug_show_project == defaultData->debug_show_project) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%sdebug.show.project %s\n",indent,comment[matched],logic[data->debug_show_project]);

   matched=0;  if (defaultData && data->debug_show_frequency_plan == defaultData->debug_show_frequency_plan) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%sdebug.show.frequency.plan %s\n",indent,comment[matched],logic[data->debug_show_frequency_plan]);

   matched=0;  if (defaultData && data->debug_show_materials == defaultData->debug_show_materials) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%sdebug.show.materials %s\n",indent,comment[matched],logic[data->debug_show_materials]);

   matched=0;  if (defaultData && data->debug_show_mode_definitions == defaultData->debug_show_mode_definitions) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%sdebug.show.mode.definitions %s\n",indent,comment[matched],logic[data->debug_show_mode_definitions]);

   matched=0;  if (defaultData && data->debug_show_impedance_details == defaultData->debug_show_impedance_details) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%sdebug.show.impedance.details %s\n",indent,comment[matched],logic[data->debug_show_impedance_details]);

   matched=0;  if (defaultData && data->debug_skip_solve == defaultData->debug_skip_solve) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%sdebug.skip.solve %s\n",indent,comment[matched],logic[data->debug_skip_solve]);

   matched=0;  if (defaultData && data->debug_tempfiles_keep == defaultData->debug_tempfiles_keep) matched=1;
   PetscPrintf(PETSC_COMM_WORLD,"%s%sdebug.tempfiles.keep %s\n",indent,comment[matched],logic[data->debug_tempfiles_keep]);

   // no default field points, so print all
   if (data->field_points_count > 0) {
      i=0;
      while (i < data->field_points_count) {
         PetscPrintf(PETSC_COMM_WORLD,"%sfield.point %g,%g\n",indent,indent,i,data->field_points_x[i],data->field_points_y[i]);
         i++;
      }
   }

   free(logic[0]);
   free(logic[1]);
   free(comment[0]);
   free(comment[1]);
}

int get_bool (char *a) {
   if (is_true(a)) return 1;
   return 0;
}

void print_invalid_entry (int *error, int lineNumber, const char *indent) {
   PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR700: Invalid entry at line %d.\n",indent,indent,lineNumber);
   *error=1;
   return;
}

char* get_project_name (const char *filename) {
   char *b=NULL;
   int i;

   if (filename == NULL) return NULL;

   // copy filename into b (since filename is const)
   b=(char *)malloc((strlen(filename)+1)*sizeof(char));
   if (b == NULL) return NULL;
   strcpy(b,filename);

   // chop off the extension
   i=strlen(b)-1;
   while (i >= 0) {
      if (b[i] == '.') {b[i]='\0'; return b;}
      i--;
   }

   return b;
}

int has_refinementFrequencyPlan (struct projectData *data) {
   int i;

   if (data == NULL) return 0;

   i=0;
   while (i < data->inputFrequencyPlansCount) {
      if (data->inputFrequencyPlans[i].refine) return 1;
      i++;
   }
   return 0;
}

int load_project_file (const char *filename, struct projectData *data, const char* indent) {
   FILE *fp;
   char *line=NULL;
   size_t len=0;
   ssize_t line_size=0;
   char *keyword=NULL;
   char *value=NULL;
   int error=0;
   int lineCount=0;
   int found;
   int lineIterationMax,lineRefinementTolerance,lineSolutionTolerance,lineRefinementVariable,lineImpedanceDefinition;
   int lineRefinementFrequency=0;
   int i;
   double x,y;
   int pointsPerDecade;
   double start,stop,step,frequency;

   if (filename == NULL) return 1;

   lineIterationMax=-1;
   lineRefinementTolerance=-1;
   lineSolutionTolerance=-1;
   lineRefinementVariable=-1;
   lineImpedanceDefinition=-1;

   fp=fopen(filename,"r");
   if (fp) {

      // check the version first

      line_size=getline(&line,&len,fp);
      while (line_size >= 0) {
         lineCount++;

         if (! is_blank(line) && len > 0) {
            line=removeNewLineChar(line);
            line=removeComment(line);

            keyword=strtok(line," ");

            if (keyword != NULL) {
               if (strcmp(keyword,data->version_name) == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     if (strcmp(value,data->version_value) != 0) {
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR701: Version mismatch. Expecting on first line: %s %s\n",
                                    indent,indent,data->version_name,data->version_value);
                        error=1;
                     }
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               } else {
                  PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR702: Missing version. Expecting on first line: %s %s\n",
                              indent,indent,data->version_name,data->version_value);
                  error=1;
               }
            }
            break;
         }
         if (line) {free(line); line=NULL;}
         line_size=getline(&line,&len,fp);
      }
      if (error) return error;

      // get the project name from the filename
      free(data->project_name);
      data->project_name=get_project_name (filename);

      // check everything else
      if (line) {free(line); line=NULL;}
      line_size=getline(&line,&len,fp);
      while (line_size >= 0) {
         lineCount++;

         if (! is_blank(line) && len > 0) {
            line=removeNewLineChar(line);
            line=removeComment(line);

            keyword=strtok(line," ");

            if (keyword != NULL) {

               //if (strcmp(keyword,"project.name") == 0) {
               //   value=strtok(NULL," ");
               //   if (is_text(value)) {
               //      free(data->project_name);
               //      data->project_name=allocCopyString(value);
               //      value=strtok(NULL," ");
               //      if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
               //   } else print_invalid_entry (&error,lineCount,indent);
               //}

               if (strcmp(keyword,"project.save.fields") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->project_save_fields=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"mesh.file") == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     free(data->mesh_file);
                     data->mesh_file=allocCopyString(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent); 
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"mesh.order") == 0) {
                  value=strtok(NULL," ");
                  if (is_int(value)) {
                     data->mesh_order=atoi(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     if (data->mesh_order < 1) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR703: Value must be >= 1 at line %d.\n",indent,indent,lineCount);
                     }
                     if (data->mesh_order > 20) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR704: Value must be <= 20 at line %d.\n",indent,indent,lineCount);
                     }
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"mesh.uniform_refinement.count") == 0) {
                  value=strtok(NULL," ");
                  if (is_int(value)) {
                     data->mesh_uniform_refinement_count=atoi(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     if (data->mesh_uniform_refinement_count < 0) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR705: Value must be >= 0 at line %d.\n",indent,indent,lineCount);
                     }
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"mesh.refinement.cutoff") == 0) {
                  value=strtok(NULL," ");
                  if (is_double(value)) {
                     data->mesh_refinement_cutoff=atof(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     if (data->mesh_refinement_cutoff < 0) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR734: Value must be >= 0 at line %d.\n",indent,indent,lineCount);
                     }
                     if (data->mesh_refinement_cutoff > 1) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR735: Value must be <= 1 at line %d.\n",indent,indent,lineCount);
                     }
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"mesh.refinement.fraction") == 0) {
                  value=strtok(NULL," ");
                  if (is_double(value)) {
                     data->mesh_refinement_fraction=atof(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     if (data->mesh_refinement_fraction <= 0) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR734: Value must be > 0 at line %d.\n",indent,indent,lineCount);
                     }
                     if (data->mesh_refinement_fraction > 1) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR735: Value must be <= 1 at line %d.\n",indent,indent,lineCount);
                     }
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"mode.definition.file") == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     free(data->mode_definition_file);
                     data->mode_definition_file=allocCopyString(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  }
               }

               else if (strcmp(keyword,"refinement.frequency") == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     free(data->refinement_frequency);
                     data->refinement_frequency=allocCopyString(value);
                     lineRefinementFrequency=lineCount;
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else {
                     free(data->refinement_frequency);
                     data->refinement_frequency=allocCopyString("highlow");
                     error=1;
                     PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR706: Value must be \"all\", \"none\", \"high\", \"low\", \"highlow (default)\", \"lowhigh\", or \"plan\" at line %d.\n",
                             indent,indent,lineCount);
                  }
                  if (! is_refinement_frequency(data->refinement_frequency)) {
                     error=1;
                     PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR707: Value must be \"all\", \"none\", \"high\", \"low\", \"highlow (default)\", \"lowhigh\", or \"plan\" at line %d.\n",
                             indent,indent,lineCount);
                  }
               }

               else if (strcmp(keyword,"refinement.variable") == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     free(data->refinement_variable);
                     data->refinement_variable=allocCopyString(value);
                     lineRefinementVariable=lineCount;
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"refinement.required.passes") == 0) {
                  value=strtok(NULL," ");
                  if (is_int(value)) {
                     data->refinement_required_passes=atoi(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     if (data->refinement_required_passes < 1) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR708: Value must be >= 1 at line %d.\n",indent,indent,lineCount);
                     }
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"refinement.tolerance") == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     free(data->refinement_tolerance);
                     data->refinement_tolerance=allocCopyString(value);
                     lineRefinementTolerance=lineCount;
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"refinement.iteration.min") == 0) {
                  value=strtok(NULL," ");
                  if (is_int(value)) {
                     data->refinement_iteration_min=atoi(value);
                     if (data->refinement_iteration_min < 1) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR709: Value must be >= 1 at line %d.\n",indent,indent,lineCount);
                     }
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"refinement.iteration.max") == 0) {
                  value=strtok(NULL," ");
                  if (is_int(value)) {
                     data->refinement_iteration_max=atoi(value);
                     lineIterationMax=lineCount;
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               //else if (strcmp(keyword,"refinement.refine.converged.modes") == 0) {
               //   value=strtok(NULL," ");
               //   if (is_bool(value)) {
               //      data->refinement_refine_converged_modes=get_bool(value);
               //      value=strtok(NULL," ");
               //      if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
               //   } else print_invalid_entry (&error,lineCount,indent);
               //}

               else if (strcmp(keyword,"materials.global.path") == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     free(data->materials_global_path);
                     data->materials_global_path=allocCopyString(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else {
                     free(data->materials_global_path);
                     data->materials_global_path=allocCopyString("./");
                  }
               }

               else if (strcmp(keyword,"materials.global.name") == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     free(data->materials_global_name);
                     data->materials_global_name=allocCopyString(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else {
                     free(data->materials_global_name);
                     data->materials_global_name=allocCopyString("");
                  }
               }

               else if (strcmp(keyword,"materials.local.path") == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     free(data->materials_local_path);
                     data->materials_local_path=allocCopyString(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else {
                     free(data->materials_local_path);
                     data->materials_local_path=allocCopyString("./");
                  }
               }

               else if (strcmp(keyword,"materials.local.name") == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     free(data->materials_local_name);
                     data->materials_local_name=allocCopyString(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else {
                     free(data->materials_local_name);
                     data->materials_local_name=allocCopyString("");
                  }
               }

               else if (strcmp(keyword,"materials.check.limits") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->materials_check_limits=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"frequency.plan.linear") == 0 || strcmp(keyword,"frequency.plan.linear.refine") == 0) {
                  value=strtok(NULL,",");
                  if (is_double(value)) {
                     start=atof(value);
                     value=strtok(NULL,",");
                     if (is_double(value)) {
                        stop=atof(value);
                        value=strtok(NULL,",");
                        if (is_double(value)) {
                           step=atof(value);
                           if (strcmp(keyword,"frequency.plan.linear.refine") == 0) {
                              add_inputFrequencyPlan (data,0,-1,start,stop,step,-1,lineCount,1);
                           } else {
                              add_inputFrequencyPlan (data,0,-1,start,stop,step,-1,lineCount,0);
                           }
                           value=strtok(NULL,",");
                           if (value) print_invalid_entry (&error,lineCount,indent);
                        } else print_invalid_entry (&error,lineCount,indent);
                     } else print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"frequency.plan.log") == 0 || strcmp(keyword,"frequency.plan.log.refine") == 0) {
                  value=strtok(NULL,",");
                  if (is_double(value)) {
                     start=atof(value);
                     value=strtok(NULL,",");
                     if (is_double(value)) {
                        stop=atof(value);
                        value=strtok(NULL,",");
                        if (is_int(value)) {
                           pointsPerDecade=atoi(value);
                           if (strcmp(keyword,"frequency.plan.log.refine") == 0) {
                              add_inputFrequencyPlan (data,1,-1,start,stop,-1,pointsPerDecade,lineCount,1);
                           } else {
                              add_inputFrequencyPlan (data,1,-1,start,stop,-1,pointsPerDecade,lineCount,0);
                           }
                           value=strtok(NULL,",");
                           if (value) print_invalid_entry (&error,lineCount,indent);
                        } else print_invalid_entry (&error,lineCount,indent);
                     } else print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"frequency.plan.point") == 0 || strcmp(keyword,"frequency.plan.point.refine") == 0) {
                  value=strtok(NULL,",");
                  if (is_double(value)) {
                     frequency=atof(value);
                     if (strcmp(keyword,"frequency.plan.point.refine") == 0) {
                        add_inputFrequencyPlan (data,2,frequency,-1,-1,-1,-1,lineCount,1);
                     } else {
                        add_inputFrequencyPlan (data,2,frequency,-1,-1,-1,-1,lineCount,0);
                     }
                     value=strtok(NULL,",");
                     if (value) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"solution.modes") == 0) {
                  value=strtok(NULL," ");
                  if (is_int(value)) {
                     data->solution_modes=atoi(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     if (data->solution_modes < 1) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR711: Value must be >= 1 at line %d.\n",indent,indent,lineCount);
                     }
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"solution.temperature") == 0) {
                  value=strtok(NULL," ");
                  if (is_double(value)) {
                     data->solution_temperature=atof(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     if (data->solution_temperature < -273.15) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR712: Value must be >= -273.15 at line %d.\n",indent,indent,lineCount);
                     } 
                     if (data->solution_temperature > 1e5) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR713: Value must be < 1e5 at line %d.\n",indent,indent,lineCount);
                     } 
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"solution.tolerance") == 0) {
                  value=strtok(NULL," ");
                  if (is_double(value)) {
                     data->solution_tolerance=atof(value);
                     lineSolutionTolerance=lineCount;
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     if (data->solution_tolerance <= 0) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR714: Value must be > 0 at line %d.\n",indent,indent,lineCount);
                     } 
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"solution.iteration.limit") == 0) {
                  value=strtok(NULL," ");
                  if (is_int(value)) {
                     data->solution_iteration_limit=atoi(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     if (data->solution_iteration_limit < 1) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR715: Value must be >= 1 at line %d.\n",indent,indent,lineCount);
                     } 
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"solution.modes.buffer") == 0) {
                  value=strtok(NULL," ");
                  if (is_int(value)) {
                     data->solution_modes_buffer=atoi(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     if (data->solution_modes_buffer < 0) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR716: Value must be >= 0 at line %d.\n",indent,indent,lineCount);
                     }
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"solution.impedance.definition") == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     free(data->solution_impedance_definition);
                     data->solution_impedance_definition=allocCopyString(value);
                     lineImpedanceDefinition=lineCount;
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else {
                     free(data->solution_impedance_definition);
                     data->solution_impedance_definition=allocCopyString("none");
                     error=1;
                     PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR717: Value must be \"PV\", \"PI\", \"VI\" or \"none (default)\" at line %d.\n",indent,indent,lineCount);
                  }
                  if (! is_impedance(data->solution_impedance_definition)) {
                     error=1;
                     PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR718: Value must be \"PV\", \"PI\", \"VI\" or \"none (default)\" at line %d.\n",indent,indent,lineCount); 
                  }
               }

               else if (strcmp(keyword,"solution.impedance.calculation") == 0) {
                  value=strtok(NULL," ");
                  if (is_text(value)) {
                     free(data->solution_impedance_calculation);
                     data->solution_impedance_calculation=allocCopyString(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else {
                     free(data->solution_impedance_calculation);
                     data->solution_impedance_calculation=allocCopyString("modal");
                     error=1;
                     PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR719: Value must be \"modal (default)\" or \"line\" at line %d.\n",indent,indent,lineCount);
                  }
                  if (! is_impedance_calculation(data->solution_impedance_calculation)) {
                     error=1;
                     PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR720: Value must be \"modal (default)\" or \"line\" at line %d.\n",indent,indent,lineCount);
                  }
               }

               else if (strcmp(keyword,"solution.check.closed.loop") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->solution_check_closed_loop=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"solution.accurate.residual") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->solution_accurate_residual=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"solution.shift.invert") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->solution_shift_invert=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"solution.use.initial.guess") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->solution_use_initial_guess=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"solution.shift.factor") == 0) {
                  value=strtok(NULL," ");
                  if (is_double(value)) {
                     data->solution_shift_factor=atof(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     if (data->solution_shift_factor < 1) {
                        error=1;
                        PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR714: Value must be >= 1 at line %d.\n",indent,indent,lineCount);
                     }
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"output.show.refining.mesh") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->output_show_refining_mesh=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"output.show.postprocessing") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->output_show_postprocessing=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"output.show.iterations") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->output_show_iterations=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"output.show.license") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->output_show_license=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"test.create.cases") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->test_create_cases=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"test.show.audit") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->test_show_audit=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"test.show.detailed.cases") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->test_show_detailed_cases=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"debug.show.memory") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->debug_show_memory=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"debug.show.project") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->debug_show_project=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"debug.show.frequency.plan") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->debug_show_frequency_plan=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"debug.show.materials") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->debug_show_materials=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"debug.show.mode.definitions") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->debug_show_mode_definitions=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"debug.show.impedance.details") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->debug_show_impedance_details=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"debug.skip.solve") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->debug_skip_solve=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"debug.tempfiles.keep") == 0) {
                  value=strtok(NULL," ");
                  if (is_bool(value)) {
                     data->debug_tempfiles_keep=get_bool(value);
                     value=strtok(NULL," ");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else if (strcmp(keyword,"field.point") == 0) {
                  value=strtok(NULL," ,");
                  if (is_double(value)) {
                     x=atof(value);
                     value=strtok(NULL," ,");
                     if (is_double(value)) {
                        y=atof(value);
                        if (data->field_points_count < 0) {
                           data->field_points_allocated=256;
                           data->field_points_x=(double *)malloc(data->field_points_allocated*sizeof(double));
                           data->field_points_y=(double *)malloc(data->field_points_allocated*sizeof(double));
                           data->field_points_count=0;
                        }
                        if (data->field_points_count == data->field_points_allocated) {
                           data->field_points_allocated+=256;
                           data->field_points_x=(double *)realloc(data->field_points_x,data->field_points_allocated*sizeof(double));
                           data->field_points_y=(double *)realloc(data->field_points_y,data->field_points_allocated*sizeof(double));
                        }
                        data->field_points_x[data->field_points_count]=x;
                        data->field_points_y[data->field_points_count]=y;
                        data->field_points_count++;
                     } else if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                     value=strtok(NULL," ,");
                     if (is_text(value)) print_invalid_entry (&error,lineCount,indent);
                  } else print_invalid_entry (&error,lineCount,indent);
               }

               else {error=1; PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR721: Invalid entry at line %d.\n",indent,indent,lineCount);}
            }
         } 

         if (line) {free(line); line=NULL;}
         line_size=getline(&line,&len,fp);
      } 

      if (line) {free(line); line=NULL;}

      // stop if an error is found so far
      if (error) {PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR731: Failed to load project.\n",indent,indent); return error;}

      // some consistency checks

      if (data->inputFrequencyPlansCount == 0) {
         error=1;
         PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR722: At least one frequency plan is required.\n",indent,indent);
      } else {
         i=0;
         while (i < data->inputFrequencyPlansCount) {
            if (data->inputFrequencyPlans[i].type == 0 || data->inputFrequencyPlans[i].type == 1) {
               if (data->inputFrequencyPlans[i].stop < data->inputFrequencyPlans[i].start) {
                  error=1;
                  PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR723: The stopping frequency must be >= to the starting frequency at line %d.\n",indent,indent,data->inputFrequencyPlans[i].lineNumber);
               }
            }
            if (data->inputFrequencyPlans[i].type == 0 && data->inputFrequencyPlans[i].step <= 0) {
               error=1;
               PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR724: The frequency step must be positive at line %d.\n",indent,indent,data->inputFrequencyPlans[i].lineNumber);
            }
            if (data->inputFrequencyPlans[i].type == 1 && data->inputFrequencyPlans[i].pointsPerDecade < 1) {
               error=1;
               PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR725: The number of points per decade must be >= 1 at line %d.\n",indent,indent,data->inputFrequencyPlans[i].lineNumber);
            }
            i++;
         }

         if (strcmp(data->refinement_frequency,"plan") == 0 && ! has_refinementFrequencyPlan(data)) {
            error=1;
            PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR732: A refinement plan is called for at line %d but no plan is provided.\n",indent,indent,lineRefinementFrequency);
         }

         if (strcmp(data->refinement_frequency,"plan") != 0 && has_refinementFrequencyPlan(data)) {
            error=1;
            PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR733: A refinement plan is not called for at line %d but a refinement plan or plans is provided.\n",indent,indent,lineRefinementFrequency);
         }

      }

      if (data->refinement_iteration_max < data->refinement_iteration_min) {
         error=1;//
         PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR726: The maximum iteration limit of %d must be >= to the minimum iteration limit of %d",indent,indent,data->refinement_iteration_max,data->refinement_iteration_min);
         if (lineIterationMax >= 0) PetscPrintf(PETSC_COMM_WORLD," at line %d.\n",lineIterationMax);
         else PetscPrintf(PETSC_COMM_WORLD,".\n");
      }

      i=1;
      while (i <= data->solution_modes) {
         if (get_refinement_tolerance (data->refinement_tolerance,i) < data->solution_tolerance) {
            error=1;
            if (lineRefinementTolerance < 0 || lineSolutionTolerance < 0) {
               PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR727: The refinement tolerance of %g must be >= the solution tolerance of %g.\n",indent,indent,
                                             get_refinement_tolerance (data->refinement_tolerance,i),data->solution_tolerance);
            } else {
               PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR727: The refinement tolerance at line %d must be >= the solution tolerance at line %d.\n",
                       indent,indent,lineRefinementTolerance,lineSolutionTolerance);
            }
            break;
         }
         i++;
      }

      found=0;
      i=1;
      while (i <= data->solution_modes) {
         if (get_refinement_variable (data->refinement_variable,i) == 0) {
            found=1;
            break;
         }
         i++;
      }
      if (found) {
         error=1;
         PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR728: Values must include \"alpha\", \"beta\", \"|gamma|\", \"|Zo|\", \"Re(Zo)\", or \"Im(Zo)\" at line %d.\n",
                 indent,indent,lineRefinementVariable);
      }

      // can't refine on impedance if no impedance definition is called out
      if (is_none_impedance(data->solution_impedance_definition)) {
         found=0;
         i=1;
         while (i <= data->solution_modes) {
            if (is_impedance_refinement_variable (data->refinement_variable,i)) {
               found=1;
               break;
            }
            i++;
         }
         if (found) {
            error=1;
            PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR729: Inconsistent definitions at lines %d and %d.\n",indent,indent,lineRefinementVariable,lineImpedanceDefinition);
         }
      }

      fclose (fp);

   } else {
      PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR730: Failed to open file \"%s\" for reading.\n",indent,indent,filename);
      error=1;
   }

   if (error) PetscPrintf(PETSC_COMM_WORLD,"%s%sERROR731: Failed to load project.\n",indent,indent);

   return error;
}

// last assigned error is 735


