#include "utmatrix.h"

#include <gtest.h>


TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)	 //проверка на то, что скопированный вектор идентичен исходному
{
	TVector<int> v1(5);
	for (int i = 0; i < 5; i++)
	{
		v1[i] = i;
	}

	TVector<int>v2(v1);

	EXPECT_EQ(v1, v2);
}

TEST(TVector, copied_vector_has_its_own_memory)	// проверка на то, что после копирования два вектора используют разную память
{
	TVector<int> v1(5);
	v1[0] = 1;

	TVector<int> v2(v1);
	v2[0] = 2;			// Меняем значение в копии

	EXPECT_NE(v1[0], v2[0]);	// Проверяем, что оригинальный вектор не изменился
}

TEST(TVector, can_get_size)	
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
	TVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)	//проверяет, что при попытке установить элемент по отрицательному индексу выбрасывается ошибка
{
	TVector<int> v(5);
	ASSERT_ANY_THROW(v[-1] = 10);
}

TEST(TVector, throws_when_set_element_with_too_large_index)	//проверяет, что при попытке установить элемент по индексу, который выходит за пределы вектора, возникает ошибка
{
	TVector<int> v(5);
	ASSERT_ANY_THROW(v[5] = 10);
}

TEST(TVector, can_assign_vector_to_itself)	//проверяет, что вектор можно присвоить самому себе, и это не вызовет ошибок
{
	TVector<int> v(5);
	for (int i = 0; i < 5; i++)
	{
		v[i] = i;
	}

	ASSERT_NO_THROW(v = v);	// присваивание вектора самому себе
	EXPECT_EQ(v[0], 0);		// проверяем, что данные остались неизменными
}

TEST(TVector, can_assign_vectors_of_equal_size)	//проверяет, что можно присвоить один вектор другому, если у них одинаковый размер
{
	TVector<int> v1(5);
	TVector<int> v2(5);

	for (int i = 0; i < 5; i++)
	{
		v1[i] = i;
	}

	ASSERT_NO_THROW(v2 = v1);	// Присваиваем вектор v1 в v2
	EXPECT_EQ(v1, v2);			// Проверяем, что вектора стали равны
}

TEST(TVector, assign_operator_change_vector_size)	//проверяет, что присваивание одного вектора другому изменяет размер вектора
{
	TVector<int> v1(5);
	TVector<int> v2(10);

	v2 = v1;	// Присваиваем вектор меньшего размера

	EXPECT_EQ(v2.GetSize(), 5);	// Проверяем, что размер изменился
}

TEST(TVector, can_assign_vectors_of_different_size)	//роверяет, что можно присвоить вектор одного размера в вектор другого размера
{
	TVector<int> v1(5);
	TVector<int> v2(10);

	for (int i = 0; i < 5; i++)
	{
		v1[i] = i;
	}
	ASSERT_NO_THROW(v2 = v1);	// Присваиваем вектор разного размера
	EXPECT_EQ(v2.GetSize(), 5);	// Проверяем, что размер изменился
	EXPECT_EQ(v2, v1);			// Проверяем, что данные корректны
}

TEST(TVector, compare_equal_vectors_return_true)	//проверяет, что оператор сравнения возвращает true для равных векторов
{
	TVector<int> v1(5);
	TVector<int> v2(5);

	for (int i = 0; i < 5; i++)
	{
		v1[i] = v2[i] = i;
	}
	EXPECT_TRUE(v1 == v2);	// Вектора равны
}

TEST(TVector, compare_vector_with_itself_return_true)	//проверяет, что вектор равен самому себе
{
	TVector<int> v(5);

	EXPECT_TRUE(v == v);	// Вектор равен самому себе
}

TEST(TVector, vectors_with_different_size_are_not_equal)	//проверяет, что вектора с разным размером не равны
{
	TVector<int> v1(5);
	TVector<int> v2(10);

	EXPECT_FALSE(v1 == v2);	// Вектора разного размера не равны
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v(5);
	for (int i = 0; i < 5; i++)
	{
		v[i] = i;
	}
	
	TVector<int> res = v + 5;		 // Прибавляем скаляр

	EXPECT_EQ(res[0], 5);			// Проверяем результат
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v(5);
	for (int i = 0; i < 5; i++)
	{
		v[i] = i;
	}

	TVector<int> res = v - 1;		 // вычитаем скаляр

	EXPECT_EQ(res[0], -1);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v(5);
	for (int i = 0; i < 5; i++)
	{
		v[i] = i;
	}
	TVector<int> res = v * 2;		// Умножаем на скаляр

	EXPECT_EQ(res[0], 0);
	EXPECT_EQ(res[1], 2);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> v1(5), v2(5);
	for (int i = 0; i < 5; i++)
	{
		v1[i] = i;
		v2[i] = 5 - i;
	}

	TVector<int> res = v1 + v2;

	EXPECT_EQ(res[0], 5);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> v1(5), v2(10);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> v1(5), v2(5);
	for (int i = 0; i < 5; i++)
	{
		v1[i] = i;
		v2[i] = 5 - i;
	}
	TVector<int> res = v1 - v2;

	EXPECT_EQ(res[0], -5);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> v1(5), v2(10);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> v1(5), v2(5);
	for (int i = 0; i < 5; i++)
	{
		v1[i] = i;
		v2[i] = 5 - i;
	}

	int res = v1 * v2;

	EXPECT_EQ(res, 20);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v1(5), v2(10);

	ASSERT_ANY_THROW(v1 * v2);

}

