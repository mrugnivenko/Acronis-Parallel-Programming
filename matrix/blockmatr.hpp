#include <iostream>
#define LINE 300

//эту часть не менял
template<class T> class blockmatrix {
public:
    blockmatrix(size_t lines, size_t columns): lines(lines), columns(columns) {
        bigbody = new T[lines * columns];
        body = new T*[lines];
        for (size_t i = 0; i < lines; i++) {
            body[i] = bigbody + i*columns;
        }
    }

    ~blockmatrix() {
        delete [] body;
        delete [] bigbody;
    }

    T * operator()(size_t line, size_t col) {
        return body[line]+col;
    }

    T * operator()(size_t line, size_t col) const {
        return body[line]+col;
    }


    bool mul(blockmatrix const &left, blockmatrix const &right) {

        if (left.columns != right.lines) return false;
        if (lines != left.lines) return false;
        if (columns != right.columns) return false;

        for (size_t i = 0; i < lines; i++) {
            for (size_t j = 0; j < columns; j++) {
                T acc = (T) 0;
                for (size_t k = 0; k < left.columns; k++) {
                    acc += *left(i,k) * *right(k, j);
                }
                *(*this)(i,j) = acc;
            }
        }
        return true;
    }

    //блочное перемножение
    bool fast_mul(blockmatrix const &left, blockmatrix const &right) {

        if (left.columns != right.lines) return false;
        if (lines != left.lines) return false;
        if (columns != right.columns) return false;

        int number_of_lef_lines = left.lines;
        int number_of_lef_columns = left.columns;
        int number_of_right_columns = right.columns;

        if(number_of_lef_lines <= LINE && number_of_lef_columns <= LINE && number_of_right_columns <= LINE){
            // если матрицы помещаются в кэш, то просто транспонируем и правую матрицу и перемножаем

            //транспонирование правой матрицы
            blockmatrix transposed_right(right.columns, right.lines);
            //берём строку правой матрицы
            for (int i = 0; i < right.lines; i++){
                T* right_pointer = right(i, 0);
                //пробегаемся по этой строке, ну то есть по столбцам только этой строки и в новую матрицу записываем эту строку, как столбец
                for (int j = 0; j < right.columns; j++) {
                    *transposed_right(j, i) = *right_pointer;
                    right_pointer++;
                }
                //потврояем для каждой строки правой матрицы
            }

            //перемножение матриц (тут строка на строку, так как транспонировали)
            T* result_pointer = (*this)(0, 0);
            for (size_t i = 0; i < lines; i++) {
                for (size_t j = 0; j < columns; j++) {
                    T elem = (T) 0;
                    T* left_pointer = left(i, 0);
                    T* right_pointer = transposed_right(j, 0);

                    for (size_t k = 0; k < left.columns; k++) {
                        elem += *left_pointer * *right_pointer;
                        left_pointer++;
                        right_pointer++;
                    }
                    *result_pointer++ = elem;
                }
            }
            return true;
        }

        if(number_of_lef_lines >= number_of_lef_columns && number_of_lef_lines >= number_of_right_columns){
            //когда левая матрица очень длинная
            blockmatrix top(0.5*number_of_lef_lines, number_of_lef_columns);
            blockmatrix bot(0.5*number_of_lef_lines, number_of_lef_columns);
            blockmatrix result_top(0.5*number_of_lef_lines, number_of_right_columns);
            blockmatrix result_bot(0.5*number_of_lef_lines, number_of_right_columns);
            //копируем соответсвующие часит
            top.copy_part_of_matrix(left, 0, 0);
            bot.copy_part_of_matrix(left, 0.5*number_of_lef_lines, 0);
            //перемножаем их
            result_top.fast_mul(top, right);
            result_bot.fast_mul(bot, right);
            //собираем в итоговую матрицу
            this->compound(result_top, 0, 0);
            this->compound(result_bot, 0.5*number_of_lef_lines, 0);

            return true;
        }

        else if(number_of_lef_columns >= number_of_lef_lines && number_of_lef_columns >= number_of_right_columns){
            //когда левая матрица очень широкая
            blockmatrix left_block(number_of_lef_lines, 0.5*number_of_lef_columns);
            blockmatrix right_block(number_of_lef_lines, 0.5*number_of_lef_columns);

            blockmatrix top_block(0.5*number_of_lef_columns, number_of_right_columns);
            blockmatrix bottom_block(0.5*number_of_lef_columns, number_of_right_columns);

            blockmatrix result_1(number_of_lef_lines, number_of_right_columns);
            blockmatrix result_2(number_of_lef_lines, number_of_right_columns);

            top_block.copy_part_of_matrix(right, 0, 0);
            bottom_block.copy_part_of_matrix(right, number_of_lef_columns/2, 0);
            left_block.copy_part_of_matrix(left, 0, 0);
            right_block.copy_part_of_matrix(left, 0, 0.5*number_of_lef_columns);

            result_1.fast_mul(left_block, top_block);
            result_2.fast_mul(right_block, bottom_block);

            this->add(result_1, result_2);

            return true;
        }

        else if(number_of_right_columns >= number_of_lef_columns && number_of_right_columns >= number_of_lef_lines){
            //когда правая матрица очень широкая
            blockmatrix left_part(number_of_lef_columns, 0.5*number_of_right_columns);
            blockmatrix right_part(number_of_lef_columns, 0.5*number_of_right_columns);
            blockmatrix res_left(number_of_lef_lines, 0.5*number_of_right_columns);
            blockmatrix res_right(number_of_lef_lines, 0.5*number_of_right_columns);
            //копируем соответсвующие часит
            left_part.copy_part_of_matrix(right, 0, 0);
            right_part.copy_part_of_matrix(right, 0, 0.5*number_of_right_columns);
            //перемножаем их
            res_left.fast_mul(left, left_part);
            res_right.fast_mul(left, right_part);
            //собираем в итоговую матрицу
            this->compound(res_left, 0, 0);
            this->compound(res_right, 0, number_of_right_columns/2);

            return true;
        }


        printf("Error\n");
        return false;
    }

    //для самого сложного случая - поэлементная сумма двух матриц
    bool add(blockmatrix const &left, blockmatrix const &right){
        for (int i = 0; i < right.lines; i++){

            T* left_pointer = left(i, 0);
            T* right_pointer = right(i, 0);
            T* final_pointer = (*this)(i, 0);

            for (int j = 0; j < right.columns; j++) {
                *final_pointer = *right_pointer + *left_pointer;
                left_pointer++;
                right_pointer++;
                final_pointer++;
            }
        }
        return true;
    }

private:
    T ** body;
    T *bigbody;
    size_t lines, columns;

    //для объединения кусочков
    void compound(blockmatrix const &child, int i_start, int j_start){
        for(int i = 0; i < child.lines; i++){

            T* child_pointer = child(i, 0);
            T* final_pointer = (*this)(i_start + i, j_start);

            for(int j = 0; j < child.columns; j++){
                *final_pointer = *child_pointer;
                final_pointer++;
                child_pointer++;
            }
        }
    }

    //копирование кусочка, чтобы не гадить так сказать
    void copy_part_of_matrix(blockmatrix const &parent, int i_start, int j_start){
        for(int i = 0; i < lines; i++){

            T* copy_pointer = (*this)(i, 0);
            T* parent_pointer = parent(i_start + i, j_start);

            for(int j = 0; j < columns; j++){
                *copy_pointer = *parent_pointer;
                copy_pointer++;
                parent_pointer++;
            }
        }
    }


};

