#ifndef EXPORTOPTIONSMODEL_H
#define EXPORTOPTIONSMODEL_H

#include <QAbstractTableModel>
#include <QStandardPaths>
#include <QDebug>
#include "headers/cpp_interface/checkboxitem.h"
#include "headers/cpp_interface/valueitem.h"
#include "headers/cpp_interface/textedititem.h"

//! qml model wrapper around ExportOptions
class ExportOptionsModel : public QAbstractListModel
{
    Q_OBJECT
//! constructors
public:
    //! initialize the model with #default_items and prepare the role names
    ExportOptionsModel(QObject * parent = nullptr)
        : QAbstractListModel(parent)
    {
        _init_options();
        _setup_role_names();
    }
    //! manage the access to FileItem member from QML
    enum ExportOptionsRoles
    {
        ExportDirectoryNameRole        = Qt::UserRole + 100
      , ExportDirectoryValueRole       = Qt::UserRole + 101
      , ImagesequencePrefixNameRole    = Qt::UserRole + 102
      , ImagesequencePrefixTooltipRole = Qt::UserRole + 103
      , ImagesequencePrefixEnabledRole = Qt::UserRole + 104
      , ImagesequencePrefixValueRole   = Qt::UserRole + 105
      , ExportAsOverlayNameRole        = Qt::UserRole + 110
      , ExportAsOverlayTooltipRole     = Qt::UserRole + 111
      , ExportAsOverlayValueRole       = Qt::UserRole + 112
      , ExportCSVNameRole              = Qt::UserRole + 113
      , ExportCSVTooltipRole           = Qt::UserRole + 114
      , ExportCSVValueRole             = Qt::UserRole + 115
      , EnabledExportButtonRole        = Qt::UserRole + 116
      , EnableLivePreviewNameRole      = Qt::UserRole + 117
      , EnableLivePreviewTooltipRole   = Qt::UserRole + 118
      , EnableLivePreviewValueRole     = Qt::UserRole + 119
    };
//! methods
public:
    //! TODO
    int rowCount(const QModelIndex & parent = QModelIndex()) const override
    {
        Q_UNUSED(parent)
        return 1;
    }
    //! a getter for the _role_names to enable the access via QML
    QHash<int, QByteArray> roleNames() const override { return _role_names; }
    //! QAbstractModel function which is called if a read in QML happens
    QVariant data(const QModelIndex & index,int role) const override
    {
        Q_UNUSED(index)
        switch (role)
        {
            case ExportDirectoryNameRole:
                return _export_directory.name();
            case ExportDirectoryValueRole:
                return _export_directory.value();
            case ImagesequencePrefixNameRole:
                return _imagesequence_prefix.name();
            case ImagesequencePrefixTooltipRole:
                return _imagesequence_prefix.tooltip();
            case ImagesequencePrefixEnabledRole:
                return _imagesequence_prefix.enabled();
            case ImagesequencePrefixValueRole:
                return _imagesequence_prefix.value();
            case ExportAsOverlayNameRole:
                return _export_as_overlay.name();
            case ExportAsOverlayTooltipRole:
                return _export_as_overlay.tooltip();
            case ExportAsOverlayValueRole:
                return _export_as_overlay.value();
            case ExportCSVNameRole:
                return _export_csv.name();
            case ExportCSVTooltipRole:
                return _export_csv.tooltip();
            case ExportCSVValueRole:
                return _export_csv.value();
            case EnableLivePreviewNameRole:
                return _enable_live_preview.name();
            case EnableLivePreviewTooltipRole:
                return _enable_live_preview.tooltip();
            case EnableLivePreviewValueRole:
                return _enable_live_preview.value();
            case EnabledExportButtonRole:
                return _enabled_export_button;
            default:
                return QVariant();
        }
    }
    //! QAbstractModel function which is called if an assignment in QML happens
    bool setData(const QModelIndex & index, const QVariant & value, int role) override
    {
        Q_UNUSED(index)
        if (role == ExportDirectoryValueRole)            _export_directory.setValue(value.toString());
        else if (role == ExportAsOverlayValueRole)       _export_as_overlay.setValue(value.toBool());
        else if (role == ExportCSVValueRole)             _export_csv.setValue(value.toBool());
        else if (role == ImagesequencePrefixValueRole)   _imagesequence_prefix.setValue(value.toString());
        else if (role == ImagesequencePrefixEnabledRole) _imagesequence_prefix.setEnabled(value.toBool());
        else if (role == EnableLivePreviewValueRole)     _enable_live_preview.setValue(value.toBool());
        else if (role == EnabledExportButtonRole)        _enabled_export_button = value.toBool();
        else return false;
        //QModelIndex toIndex(createIndex(rowCount() - 1, index.column()));
        //emit dataChanged(index, toIndex);
        resetModel();
        return true;
    }
    //! tells the views that the model's state has changed -> this triggers a "recompution" of the delegate
    Q_INVOKABLE void resetModel()
    {
        beginResetModel();
        endResetModel();
    }
    //! inits default options and triggers an update for all "listeners"
    Q_INVOKABLE void revertModelToDefault()
    {
        _init_options();
        resetModel();
    }
    //! calling c++ QStandardPaths to use them in QML
    Q_INVOKABLE QVariant getDefaultMoviesDirectory() const
    {
        return QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
    }
    //! setter
    Q_INVOKABLE void setEnabledExportButton(bool other)
    {
        QModelIndex q = createIndex(0, 0);
        setData(q, other, EnabledExportButtonRole);
    }
    //! getter
    Q_INVOKABLE QVariant enabledLivePreview(){ return _enable_live_preview.value(); }
    //! getter
    Q_INVOKABLE QVariant exportAsOverlay(){ return export_as_overlay(); }
    //! getter
    QString get_imagesequence_prefix(){ return _imagesequence_prefix.value(); }
    //! getter
    QString get_export_directory(){ return _export_directory.value(); }
    //! getter
    bool export_as_imagesequence(){ return _imagesequence_prefix.enabled(); }
    //! getter
    bool export_as_overlay(){ return _export_as_overlay.value(); }
    //! getter
    bool export_csv(){ return _export_csv.value(); }

//! methods
private:
    //! Set names to the role name hash container (QHash<int, QByteArray>)
    void _setup_role_names()
    {
        _role_names[ExportDirectoryNameRole]        = "exportDirectoryName";
        _role_names[ExportDirectoryValueRole]       = "exportDirectoryValue";
        _role_names[ImagesequencePrefixNameRole]    = "imagesequencePrefixName";
        _role_names[ImagesequencePrefixTooltipRole] = "imagesequencePrefixTooltip";
        _role_names[ImagesequencePrefixEnabledRole] = "imagesequencePrefixEnabled";
        _role_names[ImagesequencePrefixValueRole]   = "imagesequencePrefixValue";
        _role_names[ExportAsOverlayNameRole]        = "exportAsOverlayName";
        _role_names[ExportAsOverlayTooltipRole]     = "exportAsOverlayTooltip";
        _role_names[ExportAsOverlayValueRole]       = "exportAsOverlayValue";
        _role_names[ExportCSVNameRole]              = "exportCSVName";
        _role_names[ExportCSVTooltipRole]           = "exportCSVTooltip";
        _role_names[ExportCSVValueRole]             = "exportCSVValue";
        _role_names[EnabledExportButtonRole]        = "exportButtonEnabled";
        _role_names[EnableLivePreviewNameRole]      = "enableLivePreviewName";
        _role_names[EnableLivePreviewTooltipRole]   = "enableLivePreviewTooltip";
        _role_names[EnableLivePreviewValueRole]     = "enableLivePreviewValue";

    }
    //! default initial options
    void _init_options()
    {
        _export_directory.setName("Export to directory");
        _export_directory.setFont(QFont("Helvetica", 15));
        _export_directory.setEnabled(true);
        _export_directory.setValue(getDefaultMoviesDirectory().toString());

        _export_as_overlay.setName("Export as overlay");
        _export_as_overlay.setTooltip("Export the graph only");
        _export_as_overlay.setValue(false);

        _enable_live_preview.setName("Enable live preview");
        _enable_live_preview.setTooltip("Show the rendered frames");
        _enable_live_preview.setValue(true);

        _export_csv.setName("Export csv");
        _export_csv.setTooltip("Export framerate as csv file");
        _export_csv.setValue(false);

        _imagesequence_prefix.setName("Export as imagesequence");
        _imagesequence_prefix.setTooltip("Export the analysis as imagesequence");
        _imagesequence_prefix.setValue("exportsequence_");
        _imagesequence_prefix.setEnabled(true);
        _imagesequence_prefix.setFont(QFont("Helvetica", 15));

        _enabled_export_button = false;
    }

//! member
private:
    //! used by the QAbstractListModel to save the role names from QML
    QHash<int, QByteArray> _role_names;
    //! exportdirectory may be manually typed
    TextEditItem _export_directory;
    //! essentially a bool
    CheckBoxItem _export_as_overlay;
    //! essentially a bool
    CheckBoxItem _enable_live_preview;
    //! essentially a bool
    CheckBoxItem _export_csv;
    //! imageprefix name
    TextEditItem _imagesequence_prefix;
    //!
    bool _enabled_export_button;
};

#endif // EXPORTOPTIONSMODEL_H
