/**
 * @file matrix.hh
 * @author Joshua Buchanan (joshuarobertbuchanan@gmail.com)
 * @brief A matrix with n rows and m columns
 * @version 1
 * @date 2022-04-13
 *
 * @copyright Copyright (C) 2022. Intellectual property of the author(s) listed above.
 *
 */
#pragma once

#include <stdexcept>
#include <vector>

#include <iostream>

namespace ml
{
    template <class V>
    class Matrix
    {
        using Column = std::vector<V>;
        std::vector<Column> rows;

    public:
        Matrix() = default;
        inline Matrix(std::size_t const rows, std::size_t const cols)
        {
            for (std::size_t i = 0; i < rows; i++)
            {
                Column col{};
                for (std::size_t j = 0; j < cols; j++)
                {
                    col.push_back(V{0});
                }
                this->rows.push_back(col);
            }
        }

        inline std::size_t rowCount() const noexcept
        {
            return rows.size();
        }

        inline std::size_t colCount() const noexcept
        {
            return rows.at(0).size();
        }

        inline std::vector<V> &operator[](std::size_t row)
        {
            return rows.at(row);
        }

        inline std::vector<V> const &operator[](std::size_t row) const
        {
            return rows.at(row);
        }

#if __cplusplus >= 202300
        inline V &operator[](std::size_t row, std::size_t col)
        {
            return (*this)[row].at(col);
        }

        inline V const &operator[](std::size_t row, std::size_t col) const
        {
            return (*this)[row].at(col);
        }
#endif // if __cplusplus >= 202300

        template <class W = V, class X = decltype(V{0} + W{0})>
        inline Matrix<X> operator+(Matrix<W> const &that)
        {
            Matrix<X> output{rows.size(), rows.at(0).size()};
            for (std::size_t i = 0; i < rows.size(); i++)
            {
                for (std::size_t j = 0; j < rows.at(0).size(); j++)
                {
                    output[i][j] = (*this)[i][j] + that[i][j];
                }
            }
            return output;
        }
        template <class W = V, class X = decltype(V{0} + W{0})>
        inline Matrix<X> operator-(Matrix<W> const &that)
        {
            Matrix<X> output{rows.size(), rows.at(0).size()};
            for (std::size_t i = 0; i < rows.size(); i++)
            {
                for (std::size_t j = 0; j < rows.at(0).size(); j++)
                {
                    output[i][j] = (*this)[i][j] - that[i][j];
                }
            }
            return output;
        }

        template <class W = V, class X = decltype(V{0} + W{0})>
        inline Matrix<X> operator*(Matrix<W> const &that)
        {
            // index i, j of output is the dot product of row i of this
            // and column j of that.
            Matrix<X> output{rows.size(), that[0].size()};
            // for each row in this, perform the dot product with that row
            // and each column in that. The dot product is the ith row, jth
            // column index of output
            for (std::size_t i = 0; i < rows.size(); i++)
            {
                for (std::size_t j = 0; j < that[0].size(); j++)
                {
                    X accumulated = 0;
                    for (std::size_t k = 0; k < rows.at(0).size(); k++)
                    {
                        accumulated += (*this)[i][k] * that[k][j];
                    }
                    output[i][j] = accumulated;
                }
            }
            return output;
        }

        template <class W = V, class X = decltype(V{0} + W{0})>
        inline std::vector<X> operator*(std::vector<W> const &input)
        {
            std::vector<X> result;
            for (auto &row : rows)
            {
                X accumulated = 0;
                for (std::size_t i = 0; i < row.size(); i++)
                {
                    accumulated += row.at(i) * input.at(i);
                }
                result.push_back(accumulated);
            }
            return result;
        }

        template <class W = V, class X = decltype(V{0} + W{0})>
        inline Matrix<X> operator*(W const &scalar)
        {
            Matrix<X> output{rowCount(), colCount()};
            for (std::size_t i = 0; i < rowCount(); i++)
            {
                for (std::size_t j = 0; j < colCount(); j++)
                {
                    output[i][j] = scalar * (*this)[i][j];
                }
            }
            return output;
        }

        template <class W = V, class X = decltype(V{0} + W{0})>
        inline Matrix<X> operator/(W const &scalar)
        {
            Matrix<X> output{rowCount(), colCount()};
            for (std::size_t i = 0; i < rowCount(); i++)
            {
                for (std::size_t j = 0; j < colCount(); j++)
                {
                    output[i][j] = scalar / (*this)[i][j];
                }
            }
            return output;
        }

        template <class W = V, class X = decltype(V{0} + W{0})>
        inline Matrix<X> augment(Matrix<W> const &rhs)
        {
            Matrix<X> output{rowCount(), colCount() + rhs.colCount()};
            for (std::size_t i = 0; i < rowCount(); i++)
            {
                std::size_t j = 0;
                for (; j < colCount(); j++)
                {
                    output[i][j] = X{(*this)[i][j]};
                }
                for (; j - colCount() < rhs.colCount(); j++)
                {
                    output[i][j] = X{rhs[i][j - colCount()]};
                }
            }
            return output;
        }

        // this in rref form. I'm not sure if this function is 100% correct, but
        // it seems to work for all the cases I'm currently throwing at it.
        inline Matrix<V> echelon() const
        {
            // some useful lambda functions
            auto allZeros = [](std::vector<V> const &v) -> bool
            {
                for (auto const &x : v)
                {
                    if (x != 0)
                    {
                        return false;
                    }
                }
                return true;
            };
            // if there is one row or less, then we are trivially in rref form.
            if (rowCount() < 2 || !colCount())
            {
                return *this;
            }

            Matrix<V> result{*this};

            for (std::size_t i = 0; i < std::min(rowCount(), colCount()); i++)
            {
                for (std::size_t r = 0; r < rowCount(); r++)
                {
                    auto temp = result[r];
                    result[r] = result[(r + 1) % rowCount()];
                    result[(r + 1) % rowCount()] = temp;
                }

                if (result[i][i] == 0)
                {
                    continue;
                }

                // multiply the row in the diagonal by 1 / the item in the diagonal
                double factor = result[i][i];
                for (auto &x : result[i])
                {
                    x /= factor;
                    if (x == -0.0)
                    {
                        x = 0.0;
                    }
                }

                // eliminate the other elements in the column
                for (std::size_t r = 0; r < rowCount(); r++)
                {
                    if (r == i)
                    {
                        continue;
                    }
                    else
                    {
                        double k = result[r][i];
                        for (std::size_t j = 0; j < colCount(); j++)
                        {
                            result[r][j] -= k * result[i][j];
                            if (result[r][j] == -0.0)
                            {
                                result[r][j] = 0.0;
                            }
                        }
                    }
                }
                auto zeroRow = [](std::vector<V> v) -> bool
                {
                    for (auto const &x : v)
                    {
                        if (x != 0)
                        {
                            return false;
                        }
                    }
                    return true;
                };

                bool madeSwap = false;
                do
                {
                    madeSwap = false;
                    for (std::size_t r = 1; r < rowCount(); r++)
                    {
                        if (zeroRow(result[r - 1]) && !zeroRow(result[r]))
                        {
                            auto temp = result[r - 1];
                            result[r - 1] = result[r];
                            result[r] = temp;

                            madeSwap = true;
                        }
                    }
                } while (madeSwap);
            }
            // for each row, make sure that the first nonzero element is 1.
            // if not, make it 1 and zero out the other elements of that column
            // via row operations.
            for (std::size_t r = 0; r < rowCount(); r++)
            {
                for (std::size_t c = 0; c < colCount(); c++)
                {
                    if (result[r][c] != 0)
                    {
                        if (result[r][c] != 1)
                        {
                            // divide the entire row by this element
                            V pivotElement = result[r][c];
                            for (auto &elem : result[r])
                            {
                                elem /= pivotElement;
                            }
                            // zero out the other rows with respect to this
                            // column
                            for (std::size_t i = 0; i < rowCount(); i++)
                            {
                                if (i == r)
                                {
                                    continue;
                                }
                                V factor = result[i][c] / result[r][c];
                                for ( std::size_t j = 0; j < colCount(); j++)
                                {
                                    result[i][j] -= factor * result[r][j];
                                }
                            }
                        }
                        break;
                    }
                }
            }

            return result;
        }

        static inline Matrix<V> identity(std::size_t i)
        {
            Matrix<V> output{i, i};
            for (std::size_t x = 0; x < i; x++)
            {
                output[x][x] = V{1};
            }
            return output;
        }

        inline Matrix<V> inverse()
        {
            if (rowCount() != colCount())
            {
                throw std::runtime_error("No inverse!");
            }
            else
            {
                Matrix<V> superaugmented{rowCount(), 2 * colCount()};
                superaugmented = this->augment(identity(rowCount()));
                superaugmented = superaugmented.echelon();
                // result is right half of superaugmented.
                Matrix<V> result{rowCount(), colCount()};
                for (std::size_t i = 0; i < rowCount(); i++)
                {
                    for (std::size_t j = 0; j < colCount(); j++)
                    {
                        result[i][j] = superaugmented[i][j + colCount()];
                    }
                }
                return result;
            }
        }

        template <class W = V>
        bool operator==(Matrix<W> const &that) const noexcept
        {
            if (rowCount() != that.rowCount() || colCount() != that.colCount())
            {
                return false;
            }
            else
            {
                for (std::size_t i = 0; i < rowCount(); i++)
                {
                    for (std::size_t j = 0; j < colCount(); j++)
                    {
                        if ((*this)[i][j] != that[i][j])
                        {
                            return false;
                        }
                    }
                }
                return true;
            }
        }
    };

}