

// Uncomment this to visualize the orbit using OpenGL/GLUT
#define USE_OPENGL


#include "main.h"

#include <string>
#include <iomanip>
#include <bitset>
using std::to_string;

int main(int argc, char** argv)
{
	cout << setprecision(20) << endl;


	//float e = 0.5;

	//cout << sqrt((grav_constant * sun_mass / 57909176e3) * (1 - e) / (1 + e)) << endl;



	//double value = 0;

	//uint64_t bits = (uint64_t&)value;
	//bits++;
	//value = (double&)bits;

	//cout << value << endl;


	//cout << nexttowardf(0, 1) << endl;
	//cout << nexttoward(0, 1) << endl;
	//cout << nextafterf(0, 1) << endl;
	//cout << nextafter(0, 1) << endl;

	//cout << FLT_TRUE_MIN << endl;
	//cout << DBL_TRUE_MIN << endl;


//	return 0;






#ifndef USE_OPENGL

	while (1)
	{
		idle_func();
	}

	return 0;
#endif

#ifdef USE_OPENGL
	glutInit(&argc, argv);
	init_opengl(win_x, win_y);
	glutReshapeFunc(reshape_func);
	glutIdleFunc(idle_func);
	glutDisplayFunc(display_func);
	glutKeyboardFunc(keyboard_func);
	glutMouseFunc(mouse_func);
	glutMotionFunc(motion_func);
	glutPassiveMotionFunc(passive_motion_func);
	//glutIgnoreKeyRepeat(1);
	glutMainLoop();
	glutDestroyWindow(win_id);
#endif

	return 0;
}






custom_math::vector_3 grav_acceleration( custom_math::vector_3& pos, const custom_math::vector_3& vel, const MyBig G)
{
	custom_math::vector_3 grav_dir = sun_pos - pos;

	const MyBig distance = grav_dir.length();
	grav_dir.normalize();

	MyBig a = G * sun_mass / (distance * distance);
	custom_math::vector_3 accel =  grav_dir * a;
	return accel;
}




MySmall truncate_normalized_double(MyBig d)
{
	if (d <= 0.0)
		return MySmall(0);
	else if (d >= 1.0)
		return MySmall(1);

	return MySmall(d);
}



void proceed_symplectic4(custom_math::vector_3& pos, custom_math::vector_3& vel,  MyBig G,  MyBig dt)
{
	static MyBig const cr2 = pow(2.0, 1.0 / 3.0);

	static const MyBig c[4] =
	{
		1.0 / (2.0 * (2.0 - cr2)),
		(1.0 - cr2) / (2.0 * (2.0 - cr2)),
		(1.0 - cr2) / (2.0 * (2.0 - cr2)),
		1.0 / (2.0 * (2.0 - cr2))
	};

	static const MyBig d[4] =
	{
		1.0 / (2.0 - cr2),
		-cr2 / (2.0 - cr2),
		1.0 / (2.0 - cr2),
		0.0
	};

	{
		const custom_math::vector_3 grav_dir = sun_pos - pos;
		const MyBig distance = grav_dir.length();
		const MyBig Rs = 2 * grav_constant * sun_mass / (speed_of_light * speed_of_light);

		const MyBig alpha = 2.0 - sqrt(1 - (vel.length() * vel.length()) / (speed_of_light * speed_of_light));

		MyBig alpha_truncated = alpha;
		alpha_truncated -= 1.0;
		alpha_truncated = truncate_normalized_double(alpha_truncated);
		alpha_truncated += 1.0;

		const MyBig beta = sqrt(1.0 - Rs / distance);
		const MyBig beta_truncated = truncate_normalized_double(beta);

		pos += vel * c[0] * dt * beta_truncated;
		vel += grav_acceleration(pos, vel, G) * d[0] * dt * alpha_truncated;
	}

	{
		const custom_math::vector_3 grav_dir = sun_pos - pos;
		const MyBig distance = grav_dir.length();
		const MyBig Rs = 2 * grav_constant * sun_mass / (speed_of_light * speed_of_light);

		const MyBig alpha = 2.0 - sqrt(1 - (vel.length() * vel.length()) / (speed_of_light * speed_of_light));

		MyBig alpha_truncated = alpha;
		alpha_truncated -= 1.0;
		alpha_truncated = truncate_normalized_double(alpha_truncated);
		alpha_truncated += 1.0;

		const MyBig beta = sqrt(1.0 - Rs / distance);
		const MyBig beta_truncated = truncate_normalized_double(beta);

		pos += vel * c[1] * dt * beta_truncated;
		vel += grav_acceleration(pos, vel, G) * d[1] * dt * alpha_truncated;


	}

	{
		const custom_math::vector_3 grav_dir = sun_pos - pos;
		const MyBig distance = grav_dir.length();
		const MyBig Rs = 2 * grav_constant * sun_mass / (speed_of_light * speed_of_light);

		const MyBig alpha = 2.0 - sqrt(1 - (vel.length() * vel.length()) / (speed_of_light * speed_of_light));

		MyBig alpha_truncated = alpha;
		alpha_truncated -= 1.0;
		alpha_truncated = truncate_normalized_double(alpha_truncated);
		alpha_truncated += 1.0;

		const MyBig beta = sqrt(1.0 - Rs / distance);
		const MyBig beta_truncated = truncate_normalized_double(beta);

		pos += vel * c[2] * dt * beta_truncated;
		vel += grav_acceleration(pos, vel, G) * d[2] * dt * alpha_truncated;
	}

	{
		const custom_math::vector_3 grav_dir = sun_pos - pos;
		const MyBig distance = grav_dir.length();
		const MyBig Rs = 2 * grav_constant * sun_mass / (speed_of_light * speed_of_light);

		const MyBig alpha = 2.0 - sqrt(1 - (vel.length() * vel.length()) / (speed_of_light * speed_of_light));

		//MyBig alpha_truncated = alpha;
		//alpha_truncated -= 1.0;
		//alpha_truncated = truncate_normalized_double(alpha_truncated);
		//alpha_truncated += 1.0;

		const MyBig beta = sqrt(1.0 - Rs / distance);
		const MyBig beta_truncated = truncate_normalized_double(beta);

		pos += vel * c[3] * dt * beta_truncated;
		//	vel += grav_acceleration(pos, vel, G) * d[3] * dt * alpha_truncated; // last element d[3] is always 0
	}
}






void proceed_Euler(custom_math::vector_3& pos, custom_math::vector_3& vel, const MyBig G, const MyBig dt)
{
	const custom_math::vector_3 grav_dir = sun_pos - pos;	
	const MyBig distance = grav_dir.length();
	const MyBig Rs = 2 * grav_constant * sun_mass / (speed_of_light * speed_of_light);

	MyBig alpha = 2.0 - sqrt(1 - (vel.length() * vel.length()) / (speed_of_light * speed_of_light));

	MyBig alpha_truncated = alpha;
	alpha_truncated -= 1.0;
	alpha_truncated = truncate_normalized_double(alpha_truncated);
	alpha_truncated += 1.0;

	const MyBig beta = sqrt(1.0 - Rs / distance);

	const MyBig beta_truncated = truncate_normalized_double(beta);

	custom_math::vector_3 accel = grav_acceleration(pos, vel, G);

	MyBig a = dt * alpha_truncated;

	vel += accel * a;

	MyBig b = dt * beta_truncated;

	pos += vel * b;
}


long unsigned int frame_count = 0;

void idle_func(void)
{
	frame_count++;

	dt = 0.1;// (speed_of_light / mercury_vel.length()) * 1e-5;
	
	orbital_period += dt;

	custom_math::vector_3 last_pos = mercury_pos;

	//proceed_Euler(mercury_pos, mercury_vel, grav_constant, dt);
	proceed_symplectic4(mercury_pos, mercury_vel, grav_constant, dt);

	//custom_math::vector_3 next_pos = mercury_pos;
	//custom_math::vector_3 next_vel = mercury_vel;
	//proceed_Euler(next_pos, next_vel, grav_constant, dt);
//	proceed_symplectic4(next_pos, next_vel, grav_constant, dt);

	if (decreasing)
	{
		if (mercury_pos.length() > last_pos.length())
		{
			// hit perihelion
			cout << "hit perihelion" << endl;
			decreasing = false;
			periapsis = (sun_pos - last_pos).length();
			return;
		}
	}
	else
	{
		if (mercury_pos.length() < last_pos.length()
			//&&
			//mercury_pos.length() > next_pos.length()
			&& frame_count > 1)
		{
			// hit aphelion
			cout << "hit aphelion" << endl;

			apoapsis = (sun_pos - last_pos).length();

			MyBig semi_major_axis = 0.5 * (periapsis + apoapsis);

			MyBig eccentricity =

				(grav_constant * sun_mass - semi_major_axis * initial_vel * initial_vel)
				/
				(grav_constant * sun_mass + semi_major_axis * initial_vel * initial_vel);

			//exit(0);

			orbit_count++;

			custom_math::vector_3 current_dir = last_pos;
			current_dir.normalize();

			const MyBig d = current_dir.dot(previous_dir);

			const MyBig angle = acos(d);

			if (isnan(angle))
				cout << "nan" << endl;

			previous_dir = current_dir;

			const MyBig delta = 6.0f * pi * grav_constant * sun_mass / (speed_of_light * speed_of_light * (1.0f - eccentricity * eccentricity) * semi_major_axis);

			const MyBig delta2 = 24.0f * pi * pi * pi * semi_major_axis * semi_major_axis / (orbital_period*orbital_period * speed_of_light * speed_of_light * (1 - eccentricity*eccentricity));


			static const MyBig num_orbits_per_earth_century = 365.0 / 88.0 * 100;
			static const MyBig to_arcseconds = 1.0 / (pi / (180.0 * 3600.0));

			cout << "orbit " << orbit_count << endl;
			cout << "dot   " << d << endl;
			cout << "angle " << angle * num_orbits_per_earth_century * to_arcseconds << endl;
			cout << "delta " << delta * num_orbits_per_earth_century * to_arcseconds << endl;
			cout << "delta2 " << delta2 * num_orbits_per_earth_century * to_arcseconds << endl;

			orbital_period = 0;

			cout << endl;

#ifdef USE_OPENGL
			positions.clear();
#endif
			decreasing = true;

			exit(0);
		}
	}

#ifdef USE_OPENGL

	if (frame_count % 10000 == 0)
	{
		positions.push_back(mercury_pos);

		glutPostRedisplay();
	}

#endif
}


#ifdef USE_OPENGL

void init_opengl(const int& width, const int& height)
{
	win_x = width;
	win_y = height;

	if (win_x < 1)
		win_x = 1;

	if (win_y < 1)
		win_y = 1;

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(win_x, win_y);
	win_id = glutCreateWindow("orbit");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClearColor(background_colour.x.convert_to<double>(), background_colour.y.convert_to<double>(), background_colour.z.convert_to<double>(), 1);
	glClearDepth(1.0f);

	main_camera.Set(0, 0, camera_w.convert_to<double>(), camera_fov.convert_to<double>(), win_x, win_y, camera_near.convert_to<double>(), camera_far.convert_to<double>());
}

void reshape_func(int width, int height)
{
	win_x = width;
	win_y = height;

	if (win_x < 1)
		win_x = 1;

	if (win_y < 1)
		win_y = 1;

	glutSetWindow(win_id);
	glutReshapeWindow(win_x, win_y);
	glViewport(0, 0, win_x, win_y);

	main_camera.Set(main_camera.u, main_camera.v, main_camera.w, main_camera.fov, win_x, win_y, camera_near.convert_to<double>(), camera_far.convert_to<double>());
}

// Text drawing code originally from "GLUT Tutorial -- Bitmap Fonts and Orthogonal Projections" by A R Fernandes
void render_string(int x, const int y, void* font, const string& text)
{
	for (size_t i = 0; i < text.length(); i++)
	{
		glRasterPos2i(x, y);
		glutBitmapCharacter(font, text[i]);
		x += glutBitmapWidth(font, text[i]) + 1;
	}
}
// End text drawing code.

void draw_objects(void)
{
	glDisable(GL_LIGHTING);

	glPushMatrix();


	glPointSize(6.0);
	glLineWidth(6.0);


	glBegin(GL_POINTS);
	glVertex3d(sun_pos.x.convert_to<double>(), sun_pos.y.convert_to<double>(), sun_pos.z.convert_to<double>());
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 1.0, 1.0);

	for (size_t i = 0; i < positions.size(); i++)
		glVertex3d(positions[i].x.convert_to<double>(), positions[i].y.convert_to<double>(), positions[i].z.convert_to<double>());

	glEnd();





	glLineWidth(1.0f);


	// If we do draw the axis at all, make sure not to draw its outline.
	if (true == draw_axis)
	{
		glBegin(GL_LINES);

		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);

		glColor3f(0.5, 0.5, 0.5);
		glVertex3f(0, 0, 0);
		glVertex3f(-1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, -1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, -1);

		glEnd();
	}

	glPopMatrix();
}




void display_func(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the model's components using OpenGL/GLUT primitives.
	draw_objects();

	if (true == draw_control_list)
	{
		// Text drawing code originally from "GLUT Tutorial -- Bitmap Fonts and Orthogonal Projections" by A R Fernandes
		// http://www.lighthouse3d.com/opengl/glut/index.php?bmpfontortho
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, win_x, 0, win_y);
		glScalef(1, -1, 1); // Neat. :)
		glTranslatef(0, -win_y, 0); // Neat. :)
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glColor3f(control_list_colour.x.convert_to<double>(), control_list_colour.y.convert_to<double>(), control_list_colour.z.convert_to<double>());

		size_t break_size = 22;
		size_t start = 20;
		ostringstream oss;

		render_string(10, start, GLUT_BITMAP_HELVETICA_18, string("Mouse controls:"));
		render_string(10, start + 1 * break_size, GLUT_BITMAP_HELVETICA_18, string("  LMB + drag: Rotate camera"));
		render_string(10, start + 2 * break_size, GLUT_BITMAP_HELVETICA_18, string("  RMB + drag: Zoom camera"));

		render_string(10, start + 4 * break_size, GLUT_BITMAP_HELVETICA_18, string("Keyboard controls:"));
		render_string(10, start + 5 * break_size, GLUT_BITMAP_HELVETICA_18, string("  w: Draw axis"));
		render_string(10, start + 6 * break_size, GLUT_BITMAP_HELVETICA_18, string("  e: Draw text"));


		custom_math::vector_3 eye = main_camera.eye;
		custom_math::vector_3 eye_norm = eye;
		eye_norm.normalize();

		oss.clear();
		oss.str("");
		oss << "Camera position: " << eye.x << ' ' << eye.y << ' ' << eye.z;
		render_string(10, win_y - 2 * break_size, GLUT_BITMAP_HELVETICA_18, oss.str());

		oss.clear();
		oss.str("");
		oss << "Camera position (normalized): " << eye_norm.x << ' ' << eye_norm.y << ' ' << eye_norm.z;
		render_string(10, win_y - break_size, GLUT_BITMAP_HELVETICA_18, oss.str());

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		// End text drawing code.
	}

	glFlush();
	glutSwapBuffers();
}

void keyboard_func(unsigned char key, int x, int y)
{
	switch (tolower(key))
	{
	case 'w':
	{
		draw_axis = !draw_axis;
		break;
	}
	case 'e':
	{
		draw_control_list = !draw_control_list;
		break;
	}

	default:
		break;
	}
}

void mouse_func(int button, int state, int x, int y)
{
	if (GLUT_LEFT_BUTTON == button)
	{
		if (GLUT_DOWN == state)
			lmb_down = true;
		else
			lmb_down = false;
	}
	else if (GLUT_MIDDLE_BUTTON == button)
	{
		if (GLUT_DOWN == state)
			mmb_down = true;
		else
			mmb_down = false;
	}
	else if (GLUT_RIGHT_BUTTON == button)
	{
		if (GLUT_DOWN == state)
			rmb_down = true;
		else
			rmb_down = false;
	}
}

void motion_func(int x, int y)
{
	int prev_mouse_x = mouse_x;
	int prev_mouse_y = mouse_y;

	mouse_x = x;
	mouse_y = y;

	int mouse_delta_x = mouse_x - prev_mouse_x;
	int mouse_delta_y = prev_mouse_y - mouse_y;

	//if (true == lmb_down && (0 != mouse_delta_x || 0 != mouse_delta_y))
	//{
	//	main_camera.u = main_camera - u_spacer * static_cast<float>(mouse_delta_y);
	//	main_camera.v = static_cast<float>(mouse_delta_x) * v_spacer;
	//}
	//else if (true == rmb_down && (0 != mouse_delta_y))
	//{
	//	main_camera.w -= static_cast<float>(mouse_delta_y) * w_spacer;

	//	if (main_camera.w < 1.1f)
	//		main_camera.w = 1.1f;

	//}

	main_camera.Set(); // Calculate new camera vectors.
}

void passive_motion_func(int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}

#endif