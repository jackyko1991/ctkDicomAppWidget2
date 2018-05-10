/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkDICOMIndexer2_h
#define __ctkDICOMIndexer2_h

// Qt includes
#include <QObject>
#include <QSqlDatabase>

#include "ctkDICOMCoreExport.h"
#include "ctkDICOMDatabase.h"

class ctkDICOMIndexer2Private;

/// \ingroup DICOM_Core
///
/// \brief Indexes DICOM images located in local directory into an Sql database
///
class ctkDICOMIndexer2 : public QObject
{
  Q_OBJECT
public:
  static bool dcmftest(QString filename);
  explicit ctkDICOMIndexer2(QObject *parent = 0);
  virtual ~ctkDICOMIndexer2();

  ///
  /// \brief Adds directory to database and optionally copies files to
  /// destinationDirectory.
  ///
  /// Scan the directory using Dcmtk and populate the database with all the
  /// DICOM images accordingly.
  ///
  /// If includeHidden is set to false then hidden files and folders are not added.
  /// DICOM folders may be created based on series or study name, which sometimes start
  /// with a . character, therefore it is advisable to include hidden files and folders.
  ///
  Q_INVOKABLE void addDirectory(ctkDICOMDatabase& database, const QString& directoryName,
                    const QString& destinationDirectoryName = "", bool includeHidden = true);

  ///
  /// \brief Adds directory to database by using DICOMDIR and optionally copies files to
  /// destinationDirectory.
  /// Scan the directory using Dcmtk and populate the database with all the
  /// DICOM images accordingly.
  /// \return Returns false if there was an error while processing the DICOMDIR file.
  ///
  Q_INVOKABLE bool addDicomdir(ctkDICOMDatabase& database, const QString& directoryName,
                    const QString& destinationDirectoryName = "");

  ///
  /// \brief Adds a QStringList containing the file path to database and optionally copies files to
  /// destinationDirectory.
  ///
  /// Scan the directory using Dcmtk and populate the database with all the
  /// DICOM images accordingly.
  ///
  Q_INVOKABLE void addListOfFiles(ctkDICOMDatabase& database, const QStringList& listOfFiles,
                    const QString& destinationDirectoryName = "");

  ///
  /// \brief Adds a file to database and optionally copies the file to
  /// destinationDirectory.
  ///
  /// Scan the file using Dcmtk and populate the database with all the
  /// DICOM fields accordingly.
  ///
  Q_INVOKABLE void addFile(ctkDICOMDatabase& database, const QString filePath,
                    const QString& destinationDirectoryName = "");

  Q_INVOKABLE void refreshDatabase(ctkDICOMDatabase& database, const QString& directoryName);

  ///
  /// \brief Deprecated - no op.
  /// \deprecated
  /// Previously ensured that the QFuture threads have all finished indexing
  /// before returning control.
  ///
  Q_INVOKABLE void waitForImportFinished();

Q_SIGNALS:
  void foundFilesToIndex(int);
  void indexingFileNumber(int);
  void indexingFilePath(QString);
  void progress(int);
  void indexingComplete();

public Q_SLOTS:
  void cancel();

protected:
  QScopedPointer<ctkDICOMIndexer2Private> d_ptr;

private:
  Q_DECLARE_PRIVATE(ctkDICOMIndexer2);
  Q_DISABLE_COPY(ctkDICOMIndexer2);

};

#endif
