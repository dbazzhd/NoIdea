using UnityEngine;
using System.Collections;
using System.IO;

public class ExporterScript : MonoBehaviour {

	public string path;

	//----------------------------------------------------------------------------------------------------------------
	//												Start()
	//----------------------------------------------------------------------------------------------------------------
	private void Start () {
		ExportScene();
	}

	//----------------------------------------------------------------------------------------------------------------
	//												ExportScene()
	//----------------------------------------------------------------------------------------------------------------
	private void ExportScene () {

		string toExport = "function start ()\n";

		foreach (Transform child in GetComponent<Transform>()) {
			toExport += ExportObject(child.gameObject);
		}

		Debug.Log(toExport);
		File.WriteAllText(path, toExport + "\nend");
	}

	//----------------------------------------------------------------------------------------------------------------
	//												ExportObject()
	//----------------------------------------------------------------------------------------------------------------
	private string ExportObject (GameObject gameObject) {
		string result = "";

		MeshRenderer meshRenderer = gameObject.GetComponent<MeshRenderer>();
		if (meshRenderer != null) {
			result += "registerObjectName(\"" + gameObject.name + "\")\n" +  ExportCube(meshRenderer);
		}

		foreach (Transform child in gameObject.GetComponent<Transform>()) {
			result += ExportObject(child.gameObject);
		}

		return result;
	}

	//----------------------------------------------------------------------------------------------------------------
	//												ExportCube()
	//----------------------------------------------------------------------------------------------------------------
	private string ExportCube(MeshRenderer meshRenderer) {
		string color = meshRenderer.sharedMaterial.name;

		Vector3 position = meshRenderer.transform.position;
		float x = Mathf.Floor(position.x * 10.0f) / 10.0f;
		float y = Mathf.Floor(position.y * 10.0f) / 10.0f;
		float z = Mathf.Floor(position.z * 10.0f) / 10.0f;

		Vector3 scale = meshRenderer.transform.lossyScale;
		float scaleX = Mathf.Floor(scale.x * 10.0f) / 10.0f;
		float scaleY = Mathf.Floor(scale.y * 10.0f) / 10.0f;
		float scaleZ = Mathf.Floor(scale.z * 10.0f) / 10.0f;

        Vector3 rotation = Quaternion.ToEulerAngles(meshRenderer.transform.rotation);
        float rotX = rotation.x;
        float rotY = rotation.y;
        float rotZ = rotation.z;

        string meshRendererName = meshRenderer.gameObject.name.ToLower();

        string toExport =
            meshRendererName + " = createObject(\"" + meshRendererName + "\", " +
            x + "," + y + "," + z + ", " +
            //scaleX + "," + scaleY + "," + scaleZ + ", " +
            //rotX + "," + rotY + "," + rotZ + "," +
            "\"" + color + "\")\n" +
            "say(getTop())\n" +
            "setRotation(" + meshRendererName + ", " + rotX + ", " + rotY + ", " + rotZ + ")\n" +
            "setScale(" + meshRendererName + ", " + scaleX + ", " + scaleY + ", " + scaleZ + ")\n\n";
            

		return toExport;
	}
	
}
