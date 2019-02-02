#include "adlDebug_renderer.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_renderer/adlRender_manager.h"
#include "engine/adlScene_manager.h"
#include "engine/adl_resource/adlModel.h"
#include "engine/adl_resource/adlStatic_shader.h"
#include "engine/adlWindow.h"
#include "engine/adl_debug/adlLogger.h"
#include "engine/common.h"

adlDebug_renderer::adlDebug_renderer()
{
}

void adlDebug_renderer::render_sphere(adlVec3 position, adlColor color, float radius)
{
	IDebug_renderable* sphere = ADL_NEW(Sphere_renderable, position, color, radius);
	render_queue_.push_back(sphere);
}

void adlDebug_renderer::render_quad_2D(adlVec2_i32 point1, adlVec2_i32 point2, float line_width/* = 1.0f*/, adlColor color/* = adlColor::WHITE*/)
{
	IDebug_renderable* quad = ADL_NEW(Quad2D_renderable, point1, point2, line_width, color);
	render_queue_.push_back(quad);
}

void adlDebug_renderer::render_line_2D(adlVec2_i32 point1, adlVec2_i32 point2, float line_width/* = 1.0f*/, adlColor color/* = adlColor::WHITE*/)
{
	IDebug_renderable* line2D = ADL_NEW(Line2D_renderable, point1, point2, line_width, color);
	render_queue_.push_back(line2D);
}

void adlDebug_renderer::render_box(adlVec3 position, float scale/* = 1.0f*/, adlColor color/* = adlColor::WHITE*/)
{
	IDebug_renderable* box = ADL_NEW(Box_renderable, position, scale, color);
	render_queue_.push_back(box);
}

void adlDebug_renderer::render_line3D(adlVec3 point1, adlVec3 point2, float line_width/* = 1.0f*/, adlColor color/* = adlColor::WHITE*/)
{
	//std::pair<adlColor, float> pair = std::make_pair(color, line_width);

	//std::vector<float> vertices = line3Ds_[pair];
	line_vertices_.push_back(point1.x);
	line_vertices_.push_back(point1.y);
	line_vertices_.push_back(point1.z);
	line_vertices_.push_back(point2.x);
	line_vertices_.push_back(point2.y);
	line_vertices_.push_back(point2.z);
	
	//line3D_keys_.push_back(pair);

	/*IDebug_renderable* line3D = ADL_NEW(Line3D_renderable, point1, point2, line_width, color);
	render_queue_.push_back(line3D);*/
}

void adlDebug_renderer::render_point(adlVec2_i32 point, adlColor color/* = adlColor::WHITE*/, float size/* = 1.0f*/)
{
	IDebug_renderable* point_to_draw = ADL_NEW(Point_renderable, point, color, size);
	render_queue_.push_back(point_to_draw);
}

void Sphere_renderable::render()
{
	adlRender_manager* renderer = &adlRender_manager::get();
	adlScene_manager* scn_manager = &adlScene_manager::get();

	adlResource_manager* adl_rm = &adlResource_manager::get();
	adlModel_shared_ptr model = adl_rm->get_model("Sphere");
	adlShader_shared_ptr shader = adl_rm->get_shader("debug_render");

	adlTransform transform = adlTransform::identity();

	transform.o = position_;
	transform.scale = adlVec3(radius_);

	const adlMat4& projection_matrix = renderer->get_projection_matrix();
	const adlMat4& view_matrix = scn_manager->get_camera()->get_view_matrix();
	const adlMat4& model_matrix = transform.get_transformation_matrix();

	shader->start();
	
	shader->load_color(color_.to_vec3());
	shader->load_projection_matrix(projection_matrix);
	shader->load_view_matrix(view_matrix);
	shader->load_model_matrix(model_matrix);
	shader->load_switch(true);

	model->draw(shader, model_matrix);

	shader->stop();
}

void Quad2D_renderable::render()
{
	adlVec2 ndc1 = adlMath::to_ndc(point1_);
	adlVec2 ndc2 = adlMath::to_ndc(point2_);

	float min_x = adlMath::min2(ndc1.x, ndc2.x);
	float min_y = adlMath::min2(ndc1.y, ndc2.y);

	float max_x = adlMath::max2(ndc1.x, ndc2.x);
	float max_y = adlMath::max2(ndc1.y, ndc2.y);

	glLineWidth(line_width_);
	adlVec3 color_vec = color_.to_vec3();
	glColor3f(color_vec.x, color_vec.y, color_vec.z);
	glBegin(GL_LINES);
	//Left
	glVertex3f(min_x, min_y, 0.0f);
	glVertex3f(min_x, max_y, 0.0f);

	//Bottom
	glVertex3f(min_x, min_y, 0.0f);
	glVertex3f(max_x, min_y, 0.0f);

	//Right
	glVertex3f(max_x, max_y, 0.0f);
	glVertex3f(max_x, min_y, 0.0f);

	//Top
	glVertex3f(max_x, max_y, 0.0f);
	glVertex3f(min_x, max_y, 0.0f);
	glEnd();
	glLineWidth(1.0f);
}

void Point_renderable::render()
{
	adlVec3 color_vec = color_.to_vec3();
	adlVec2 ndc = adlMath::to_ndc(screen_pos_);

	glPointSize(size_);

	glBegin(GL_POINTS);
	glColor3f(color_vec.x, color_vec.y, color_vec.z);
	glVertex3f(ndc.x, ndc.y, 0.0f);
	glEnd();

	glPointSize(1.0f);
}

void Line2D_renderable::render()
{
	adlVec2 ndc1 = adlMath::to_ndc(point1_);
	adlVec2 ndc2 = adlMath::to_ndc(point2_);

	glLineWidth(line_width_);
	adlVec3 color_vec = color_.to_vec3();
	glColor3f(color_vec.x, color_vec.y, color_vec.z);
	glBegin(GL_LINES);
	glVertex3f(ndc1.x, ndc1.y, 0.0f);
	glVertex3f(ndc2.x, ndc2.y, 0.0f);
	glEnd();
	glLineWidth(1.0f);
}

void Box_renderable::render()
{
	adlRender_manager* renderer = &adlRender_manager::get();
	adlScene_manager* scn_manager = &adlScene_manager::get();

	adlResource_manager* adl_rm = &adlResource_manager::get();
	adlModel_shared_ptr model = adl_rm->get_model("Cube");
	adlShader_shared_ptr shader = adl_rm->get_shader("debug_render");

	adlTransform transform = adlTransform::identity();

	transform.o = position_;
	transform.scale = adlVec3(scale_);

	const adlMat4& projection_matrix = renderer->get_projection_matrix();
	const adlMat4& view_matrix = scn_manager->get_camera()->get_view_matrix();
	const adlMat4& model_matrix = transform.get_transformation_matrix();

	shader->start();

	shader->load_color(color_.to_vec3());
	shader->load_projection_matrix(projection_matrix);
	shader->load_view_matrix(view_matrix);
	shader->load_model_matrix(model_matrix);
	shader->load_switch(true);

	model->draw(shader, model_matrix);

	shader->stop();
}

void Line3D_renderable::render()
{
	adlRender_manager* renderer = &adlRender_manager::get();
	adlScene_manager* scn_manager = &adlScene_manager::get();

	adlMat4 projection_matrix = renderer->get_projection_matrix();
	adlMat4 view_matrix = scn_manager->get_camera()->get_view_matrix();

	adlResource_manager* adl_rm = &adlResource_manager::get();
	adlShader_shared_ptr shader = adl_rm->get_shader("debug_render");

	adlVec3 p1 = adlVec4(position_.x, position_.y, position_.z, 1.0f);
	adlVec3 p2 = adlVec4(point2_.x, point2_.y, point2_.z, 1.0f);

	float points[] = { p1.x, p1.y, p1.z, p2.x, p2.y, p2.z };
	uint32 vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uint32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &points[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glLineWidth(line_width_);
	shader->start();

	shader->load_color(color_.to_vec3());
	shader->load_projection_matrix(projection_matrix);
	shader->load_view_matrix(view_matrix);
	shader->load_switch(false);

	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_LINES, 0, 2);

	glDisableVertexAttribArray(0);

	glBindVertexArray(0);

	shader->stop();
	glLineWidth(1.0f);

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void adlDebug_renderer::render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_DEPTH_TEST);

	for (auto renderable : render_queue_)
	{
		renderable->render();
	}

	if (line_vertices_.size() != 0)
	{
		adlRender_manager* renderer = &adlRender_manager::get();
		adlScene_manager* scn_manager = &adlScene_manager::get();

		adlMat4 projection_matrix = renderer->get_projection_matrix();
		adlMat4 view_matrix = scn_manager->get_camera()->get_view_matrix();

		adlResource_manager* adl_rm = &adlResource_manager::get();
		adlShader_shared_ptr shader = adl_rm->get_shader("debug_render");

		uint32 vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		uint32 vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, line_vertices_.size() * sizeof(float), &line_vertices_[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glLineWidth(1.0f);
		shader->start();

		adlColor color = adlColor::YELLOW;

		shader->load_color(color.to_vec3());
		shader->load_projection_matrix(projection_matrix);
		shader->load_view_matrix(view_matrix);
		shader->load_switch(false);

		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);

		glDrawArrays(GL_LINES, 0, line_vertices_.size());

		glDisableVertexAttribArray(0);

		glBindVertexArray(0);

		shader->stop();
		glLineWidth(1.0f);

		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void adlDebug_renderer::clear_render_queue()
{
	for (auto renderable : render_queue_)
	{
		ADL_DELETE(renderable);
	}

	line3Ds_.clear();
	line3D_keys_.clear();
	line_vertices_.clear();

	render_queue_.clear();
}

void adlDebug_renderer::render_bounding_boxes()
{
	
	adlScene_manager* scn_manager = &adlScene_manager::get();
	//const std::vector<adlActor_shared_ptr>& actors = scn_manager->get_all_actors();
	const std::vector<adlActor*>& actors = scn_manager->getAllActors();

	for (auto actor : actors)
	{
		adlMat4 model_matrix = actor->get_transform().get_transformation_matrix();
		adlModel_shared_ptr model = actor->get_model();
		if (model == nullptr)
		{
			continue;
		}
		const std::vector<adlMesh_shared_ptr>& meshes = model->get_all_meshes();
		for (auto mesh : meshes)
		{
			adlBounding_box bb = mesh->get_bounding_box();

			adlVec3 up_left_back = model_matrix.transform_to_parent(bb.up_left_back());
			adlVec3 up_left_front = model_matrix.transform_to_parent(bb.up_left_front());
			adlVec3 up_right_back = model_matrix.transform_to_parent(bb.up_right_back());
			adlVec3 up_right_front = model_matrix.transform_to_parent(bb.up_right_front());

			adlVec3 bottom_left_back = model_matrix.transform_to_parent(bb.bottom_left_back());
			adlVec3 bottom_left_front = model_matrix.transform_to_parent(bb.bottom_left_front());
			adlVec3 bottom_right_back = model_matrix.transform_to_parent(bb.bottom_right_back());
			adlVec3 bottom_right_front = model_matrix.transform_to_parent(bb.bottom_right_front());

			render_line3D(up_left_back, up_right_back, bounding_box_line_width_, bounding_box_color_);
			render_line3D(up_left_back, up_left_front, bounding_box_line_width_, bounding_box_color_);
			render_line3D(up_left_front, up_right_front, bounding_box_line_width_, bounding_box_color_);
			render_line3D(up_right_front, up_right_back, bounding_box_line_width_, bounding_box_color_);

			render_line3D(up_left_back, bottom_left_back, bounding_box_line_width_, bounding_box_color_);
			render_line3D(up_right_back, bottom_right_back, bounding_box_line_width_, bounding_box_color_);
			render_line3D(up_right_front, bottom_right_front, bounding_box_line_width_, bounding_box_color_);
			render_line3D(up_left_front, bottom_left_front, bounding_box_line_width_, bounding_box_color_);

			render_line3D(bottom_left_back, bottom_right_back, bounding_box_line_width_, bounding_box_color_);
			render_line3D(bottom_left_back, bottom_left_front, bounding_box_line_width_, bounding_box_color_);
			render_line3D(bottom_left_front, bottom_right_front, bounding_box_line_width_, bounding_box_color_);
			render_line3D(bottom_right_front, bottom_right_back, bounding_box_line_width_, bounding_box_color_);
		}
		
	}
}