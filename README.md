# physics_code

Programs I did in my Masters or PhD in Physics.

3_body_problem : A numerical code in Mathematica for solving the 3 body problem with gravitational, elastic and electric forces among the 3 bodies.

Lab_plot&fit_program: Work done in Laboratory classes. Contains a program (done in C++ with CERN's ROOT libraries) that performs plots, histograms or fits of the experimental data. The development of this program was essential since we needed a high degree of personalisation in our plots. My group had the best grade in the class.

python_ObjectOriented_exam: When I was learning Python a friend of mine gave me some class material. This was my attempt at solving this exam on Python object-oriented programming.

fluid_sim: Tentative numerical simulation (in C++) of the behaviour of a fluid after an explosion (a spike in pressure & energy). 

programming: Files from my first programming class, where I learned C. trabalhosPI contains solutions to several exercises. proj is the final project folder. The final project consised in the development of a simulation of a microscope (translating optic physics into code, caring about the UX).

computational_physics: Files from my second programming class - computational physics - where I learned C++. B09/Trabx contains the midterms. Trab1 consisted in developing numerical methods to operate on polynomial functions. 02 consisted in developing numerical methods to solve several physics problems. Projecto is the final project folder. Again, it consisted in developing numerical methods to solve physics problems, but there was an emphasis in data visualisation.

reinforcement_learning: This was for a class where the intention was for the student to develop one idea and then write a paper on it. I used C++ to develop a simulation of population growth and evolution based on the idea of Reinforcement Learning. The model correctly predicts the development of a population around food sources and their migration in search of a new one when the known ones become saturated. Additionally, I compared the model to a pure random one and the population number was fitted to a logistic function for an interesting evolution of the system. Detais can be read in the paper file "II_78889.pdf". Source code can be found in work/codes/main_code/life.C .

neutrino/vlq_parameter_space: Code I developed in my PhD, done in Python. It contains a generator of the complete parameter space of the Standard Model + 3 right-handed neutrinos or 1 up vector-like quark (vlq). It is then possible to restrict the parameter space using experimental bounds/data. 
In the vlq case, it contains a machine learning minimization algorithm that finds the region of the parameter space that best fits the experimental data.
