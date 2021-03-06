/*
* kimageio.h -- Declaration of interface to the KDE Image IO library.
* Copyright (c) 1998 Sirtaj Singh Kang <taj@kde.org>
*
* This library is distributed under the conditions of the GNU LGPL.
*/

#ifndef KIO_KIMAGEIO_H
#define KIO_KIMAGEIO_H

#include <QtCore/QStringList>
#include <QtCore/QString>

#include <kdelibs4support_export.h>

/**
 * Methods to get information about image format names and
 * the corresponding mime type. Also, you can get information about supported
 * image types without loading all the imageformat plugins.
 *
 * The image processing backends are written as image handlers compatible
 * with the QImageIOHandler format. The backends are Qt imageformat plugins.
 * Each format can be identified by a unique type id string.
 *
 * \b Formats:
 *
 * Currently supported formats include:
 * @li BMP     \<read\> \<write\>
 * @li EPS     \<read\> \<write\>
 * @li EXR     \<read\>
 * @li G3      \<read\>
 * @li GIF     \<read\>
 * @li ICO     \<read\>
 * @li JP2     \<read\> \<write\>
 * @li JPEG    \<read\> \<write\>
 * @li NETPBM  \<read\> \<write\>
 * @li PCX     \<read\> \<write\>
 * @li PNG     \<read\> \<write, only with newer libraries\>
 * @li TGA     \<read\> \<write\>
 * @li TIFF    \<read\>
 * @li XBM     \<read\> \<write\>
 * @li XPM     \<read\> \<write\>
 * @li XV      \<read\> \<write\>
 *
 */
namespace KImageIO
{
/**
 * Possible image file access modes.
 *
 * Used in various KImageIO static function.
 **/
enum Mode { Reading, Writing };

#if !defined(KDELIBS4SUPPORT_NO_DEPRECATED)
/**
 * Returns a list of patterns of all KImageIO supported formats.
 *
 * These patterns can be passed to KFileDialog::getOpenFileName()
 * or KFileDialog::getSaveFileName(), for example.
 *
 * @param mode Tells whether to retrieve modes that can be read or written.
 * @return a space-separated list of file globs that describe the
 * supported formats
 * @deprecated since 5.0, use QIMageReader/QImageWriter::supportedMimeTypes() and
 * QFileDialog::setMimeTypeFilters() instead.
 */
KDELIBS4SUPPORT_DEPRECATED_EXPORT QString pattern(Mode mode = Reading);
#endif

#if !defined(KDELIBS4SUPPORT_NO_DEPRECATED)
/**
 * Returns the type of a MIME type.
 * @param mimeType the MIME type to search
 * @return type id(s) of the MIME type or QStringList() if the MIME type
 *         is not supported
 * @deprecated since 5.0, use QMimeType::suffixes() instead().
 */
KDELIBS4SUPPORT_DEPRECATED_EXPORT QStringList typeForMime(const QString &mimeType);
#endif

#if !defined(KDELIBS4SUPPORT_NO_DEPRECATED)
/**
 * Returns a list of all KImageIO supported formats.
 *
 * @param mode Tells whether to retrieve modes that can be read or written.
 * @return a list of the type ids
 * @deprecated since 5.0, use QImageReader/QImageWriter::supportedImageFormats() instead.
 */
KDELIBS4SUPPORT_DEPRECATED_EXPORT QStringList types(Mode mode = Writing);
#endif

#if !defined(KDELIBS4SUPPORT_NO_DEPRECATED)
/**
 *  Returns a list of MIME types for all KImageIO supported formats.
 *
 * @param mode Tells whether to retrieve modes that can be read or written.
 * @return a list if MIME types of the supported formats
 * @deprecated since 5.0, use QImageReader/QImageWriter::supportedMimeTypes() instead.
 */
KDELIBS4SUPPORT_DEPRECATED_EXPORT QStringList mimeTypes(Mode mode = Writing);
#endif

#if !defined(KDELIBS4SUPPORT_NO_DEPRECATED)
/**
 * Test to see whether a MIME type is supported to reading/writing.
 * @param _mimeType the MIME type to check
 * @param _mode Tells whether to check for reading or writing capabilities
 * @return true if the type is supported
 * @deprecated since 5.0, use QImageReader/QImageWriter::supportedMimeTypes() instead.
 **/
KDELIBS4SUPPORT_DEPRECATED_EXPORT bool isSupported(const QString &mimeType, Mode mode = Writing);
#endif
}

#endif
