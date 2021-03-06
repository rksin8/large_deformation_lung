    for (unsigned int s=0; s<elem->n_sides(); s++)
    {
      if (elem->neighbor(s) == NULL)
      {   
        AutoPtr<Elem> side (elem->build_side(s));

        for (unsigned int ns=0; ns<side->n_nodes(); ns++)
        {

          for (unsigned int n=0; n<elem->n_nodes(); n++)
          {
      
						Node *node = elem->get_node(n);
            	 
			const Real xf = (*node)(0);
      Real yf = (*node)(1);
      Real zf = (*node)(2);
								
			const Point A    = es.parameters.get<Point>("A");
			const Point b    = es.parameters.get<Point>("b");
			Real pi=3.14159;
      Real fac=0.5*(1+sin(1*pi*(time/2)+(3.0/2.0)*pi)); //-paper
			es.parameters.set<Real> ("fac") =fac;

			Point diagAt(fac*A(0) + REFSCALE,fac*A(1)+ REFSCALE,fac*A(2)+ REFSCALE);						
			Point bt(fac*b(0),fac*b(1),fac*b(2));
									
			//Go from  value			(FRC)
			Point p;
			for (unsigned int d = 0; d < 3; ++d) {
			  unsigned int source_dof = node->dof_number(1, d+4, 0);
			  Real value = ref_sys.current_local_solution->el(source_dof);
			  p(d)=value;
			}
						
            int source_dof = node->dof_number(last_non_linear_soln.number(), u_var, 0);
            if((source_dof<12345678) && (source_dof>-1)){
				Real value = last_non_linear_soln.current_local_solution->el(source_dof) - ref_sys.current_local_solution->el(source_dof);
//				rows_values.push_back(value-(xf*diagAt(0)+bt(0)));
								rows_values.push_back(value-(p(0)*diagAt(0)+bt(0)));

       			  rows.push_back(source_dof);

							
						//	std::cout<< "p(0) "<< p(0) <<std::endl;
						//	std::cout<< "frc "<< ref_sys.current_local_solution->el(source_dof) <<std::endl;

            }

            source_dof = node->dof_number(last_non_linear_soln.number(), v_var, 0);
            if((source_dof<12345678) && (source_dof>-1)){
							 Real value = last_non_linear_soln.current_local_solution->el(source_dof) - ref_sys.current_local_solution->el(source_dof);							
							//	rows_values.push_back(value-(yf*diagAt(1)+bt(1)));
									rows_values.push_back(value-(p(1)*diagAt(1)+bt(1)));

								rows.push_back(source_dof);
						
            }

            source_dof = node->dof_number(last_non_linear_soln.number(), w_var, 0);
            if((source_dof<12345678) && (source_dof>-1)){
							Real value = last_non_linear_soln.current_local_solution->el(source_dof) - ref_sys.current_local_solution->el(source_dof);
							
//								rows_values.push_back(value-(zf*diagAt(2)+bt(2)));

								rows_values.push_back(value-(p(2)*diagAt(2)+bt(2)));

								rows.push_back(source_dof);
				
            }
            



          }





        }
      } //if (elem->neighbor(s) == NULL)
    } // end boundary condition section  


