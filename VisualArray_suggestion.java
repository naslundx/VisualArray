import java.util.List;
import java.util.ArrayList;
import javafx.collections.ObservableList;
import javafx.collections.ListChangeListener;
import javafx.collections.FXCollections;

// Main idea: Using observableList from JavaFX
// However, this does not simulate an array.
 
// Use Java Collections to create the List.
List<String> list = new ArrayList<String>();

// Now add observability by wrapping it with ObservableList.
ObservableList<String> observableList = FXCollections.observableList(list);

observableList.addListener(new ListChangeListener() {
    @Override
    public void onChanged(ListChangeListener.Change change) {
        System.out.println("Detected a change! ");
    }
});

// Changes to the observableList WILL be reported.
