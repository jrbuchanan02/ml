/**
 * @file matrix.tcc
 * @author Joshua Buchanan (joshuarobertbuchanan@gmail.com)
 * @brief This C++ file is meant too be included only in matrix.hh
 * @version 1
 * @date 2022-04-14
 *
 * @copyright Copyright (C) 2022. Intellectual property of the author(s) listed above.
 *
 */

template <CONCEPT_NAMESPACE Floating V>
ml::Matrix<V>::Matrix(std::size_t const rows, std::size_t const cols)
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

template <CONCEPT_NAMESPACE Floating V>
std::size_t ml::Matrix<V>::rowCount() const noexcept
{
    return rows.size();
}

template <CONCEPT_NAMESPACE Floating V>
std::size_t ml::Matrix<V>::colCount() const noexcept
{
    return rows.empty() ? 0 : rows.at(0).size();
}

template <CONCEPT_NAMESPACE Floating V>
std::vector<V> &ml::Matrix<V>::operator[](std::size_t row)
{
    return rows.at(row);
}

template <CONCEPT_NAMESPACE Floating V>
std::vector<V> const &ml::Matrix<V>::operator[](std::size_t row) const
{
    return rows.at(row);
}

template <CONCEPT_NAMESPACE Floating V>
template <CONCEPT_NAMESPACE Floating W, CONCEPT_NAMESPACE Floating X>
ml::Matrix<X> ml::Matrix<V>::operator+(Matrix<W> const &that)
{
    Matrix<X> output{rowCount(), colCount()};
    for (std::size_t i = 0; i < rowCount(); i++)
    {
        for (std::size_t j = 0; j < colCount(); j++)
        {
            output[i][j] = (*this)[i][j] + that[i][j];
        }
    }
    return output;
}

template <CONCEPT_NAMESPACE Floating V>
template <CONCEPT_NAMESPACE Floating W, CONCEPT_NAMESPACE Floating X>
ml::Matrix<X> ml::Matrix<V>::operator-(Matrix<W> const &that)
{
    Matrix<X> output{rowCount(), colCount()};
    for (std::size_t i = 0; i < rowCount(); i++)
    {
        for (std::size_t j = 0; j < colCount(); j++)
        {
            output[i][j] = (*this)[i][j] - that[i][j];
        }
    }
    return output;
}

template <CONCEPT_NAMESPACE Floating V>
template <CONCEPT_NAMESPACE Floating W, CONCEPT_NAMESPACE Floating X>
ml::Matrix<X> ml::Matrix<V>::operator*(Matrix<W> const &that)
{
    // index i, j of output is the dot product of row i of this
    // and column j of that.
    Matrix<X> output{rowCount(), that.colCount()};
    // for each row in this, perform the dot product with that row
    // and each column in that. The dot product is the ith row, jth
    // column index of output
    for (std::size_t i = 0; i < rowCount(); i++)
    {
        for (std::size_t j = 0; j < that.colCount(); j++)
        {
            X accumulated = 0;
            for (std::size_t k = 0; k < colCount(); k++)
            {
                accumulated += (*this)[i][k] * that[k][j];
            }
            output[i][j] = accumulated;
        }
    }
    return output;
}

template <CONCEPT_NAMESPACE Floating V>
template <CONCEPT_NAMESPACE Floating W, CONCEPT_NAMESPACE Floating X>
std::vector<X> ml::Matrix<V>::operator*(std::vector<W> const &input)
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

template <CONCEPT_NAMESPACE Floating V>
template <CONCEPT_NAMESPACE Floating W, CONCEPT_NAMESPACE Floating X>
ml::Matrix<X> ml::Matrix<V>::operator*(W const &scalar)
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

template <CONCEPT_NAMESPACE Floating V>
template <CONCEPT_NAMESPACE Floating W, CONCEPT_NAMESPACE Floating X>
ml::Matrix<X> ml::Matrix<V>::operator/(W const &scalar)
{
    Matrix<X> output{rowCount(), colCount()};
    for (std::size_t i = 0; i < rowCount(); i++)
    {
        for (std::size_t j = 0; j < colCount(); j++)
        {
            output[i][j] = (*this)[i][j] / scalar;
        }
    }
    return output;
}

template<CONCEPT_NAMESPACE Floating V>
template<CONCEPT_NAMESPACE Floating W, CONCEPT_NAMESPACE Floating X>
ml::Matrix<X> ml::Matrix<V>::augment(Matrix<W> const &that)
{
    Matrix<X> output { rowCount(), colCount() + that.colCount()};
    for ( std::size_t i = 0; i < rowCount(); i++)
    {
        std::size_t j = 0;
        for (; j < colCount(); j++)
        {
            output[i][j] = X{(*this)[i][j]};
        }
        for (; j - colCount() < that.colCount(); j++)
        {
            output[i][j] = X{that[i][j - colCount()]};
        }
    }
    return output;
}


template<CONCEPT_NAMESPACE Floating V>
ml::Matrix<V> ml::Matrix<V>::echelon() const
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
                        for (std::size_t j = 0; j < colCount(); j++)
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

template<CONCEPT_NAMESPACE Floating V>
ml::Matrix<V> ml::Matrix<V>::inverse()
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

template <CONCEPT_NAMESPACE Floating V>
template <CONCEPT_NAMESPACE Floating W>
bool ml::Matrix<V>::operator==(Matrix<W> const &that) const noexcept
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

#if __cplusplus >= 202300

template <CONCEPT_NAMESPACE Floating V>
V &ml::Matrix<V>::operator[](std::size_t row, std::size_t col)
{
    return (*this)[row].at(col);
}

template <CONCEPT_NAMESPACE Floating V>
V const &ml::Matrix<V>::operator[](std::size_t row, std::size_t col) const
{
    return (*this)[row].at(col);
}
#endif