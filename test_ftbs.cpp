bool test_ftbs();

int main()
{
	bool testResults = test_ftbs();

	std::cout << "FTBS Test Results: " + testResults << std::endl;
}

inline bool test_ftbs() 
{
	vector p1 = { 1.0f, 1.0f, 1.0f };
	vector p2 = { 5.0f, 6.0f, 4.0f };
	vector p3 = { 2.0f, 2.0f, 2.0f };

	vector center = { 0.0f, 0.0f, 0.0f };

	fixed_tightly_bounding_sphere sphere;
	init_sphere(&sphere, &center);

	fixed_tightly_bounding_sphere test_base_sphere;
	init_sphere(&test_base_sphere, &center);

	insert_point(&test_base_sphere, &p2);

	std::cout << "FTBS Test - Insert" << std::endl;

	insert_point(&sphere, &p1);

	std::cout << "FTBS Test - Remove" << std::endl;

	remove_point(&sphere, &p1);

	std::cout << "FTBS Test - Duplicate Pointer Insert" << std::endl;

	insert_point(&sphere, &p1);
	insert_point(&sphere, &p1);

	std::cout << "FTBS Test - Duplicate Value Insert" << std::endl;

	insert_point(&sphere, &p2);

	std::cout << "FTBS Test - Invalid Remove" << std::endl;

	remove_point(&sphere, &p3);

	std::cout << "FTBS Test - Duplicate Remove" << std::endl;

	remove_point(&sphere, &p1);
	remove_point(&sphere, &p1);

	return (sphere.p->points == test_base_sphere.p->points && sphere.radius == test_base_sphere.radius);
}